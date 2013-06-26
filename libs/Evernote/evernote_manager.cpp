#include <string>
#include <QApplication>
#include "evernote_manager.h"

using namespace std;
using namespace boost;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace evernote::edam;

namespace evernote_kindle
{

/**
 * The ENML preamble to every Evernote note.
 * Note content goes between <en-note> and </en-note>
 */
static const QString NOTE_PREFIX = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">"
                                "<en-note>";

/**
 * The ENML postamble to every Evernote note
 */
static const QString NOTE_SUFFIX = "</en-note>";
    
/**
 * Reading shared title
 * <![CDATA[<div><div style=\"width:90%; max-width:600px; margin:0px auto; padding:5px; font-size:12pt; font-family:Times\"><h2 style=\"font-size:18pt; text-align:right;\">]]>
*/
static const QString READING_SHARED_TITLE =
    //"<![CDATA[
    "<div><div style=\"width:90%; max-width:600px; margin:0px auto; padding:5px; font-size:12pt; font-family:Times\"><h2 style=\"font-size:18pt; text-align:right;\">";
    //"]]>";
    
/**
 * <string name="reading__shared__title_suffix"><![CDATA[ </h2> ]]></string>
*/
static const QString READING_SHARED_TITLE_SUFFIX =
    //"<![CDATA["
    "</h2>";
    //"]]>";

/**
 * <string name="reading__shared__author">
 <![CDATA[
 <h5 style=\"font-size:12pt; text-align:right; color:gray;\">%s</h5>
 ]]>
 </string>
*/
static const QString READING_SHARED_AUTHOR =
    //"<![CDATA["
    "<h5 style=\"font-size:12pt; text-align:right; color:gray;\">%1</h5>";
    //"]]>";

/**
 * <string name="reading__shared__chapter_num">Chapter %1</string>
 */
static const QString READING_SHARED_CHAPTER = "Chapter %1";
    
/**
 *     <string name="reading__shared__comment">
 <![CDATA[
 <div style=\"padding-top:0.5em; padding-bottom:0.5em; %1$s \">
 <div style=\"font-size:10pt; margin-bottom:0.2em;\">
 <div style=\"display:inline-block; width:0.25em; height:0.9em; margin-right:0.5em; background-color:rgb(%2$s);\">&nbsp;
 </div>
 <span style=\"color:darkgray\">%3$s</span>
 </div>
 <div style=\"font-size:12pt;\">
 <span>%4$s</span>
 </div>
 %5$s
 </div>
 ]]>
 </string>
 */
static const QString READING_SHARED_COMMENT =
    //" <![CDATA["
    "<div style=\"padding-top:0.5em; padding-bottom:0.5em; %1 \">"
    "<div style=\"font-size:10pt; margin-bottom:0.2em;\">"
    "<div style=\"display:inline-block; width:0.25em; height:0.9em; margin-right:0.5em; background-color:rgb(%2);\">&nbsp;"
    "</div>"
    "<span style=\"color:darkgray\">%3</span>"
    "</div>"
    "<div style=\"font-size:12pt;\">"
    "<span>%4</span>"
    "</div>"
    "%5"
    "</div>";
    //"]]>";

/**
 *     <string name="reading__shared__comment_split">
 <![CDATA[
 border-top:1px dotted lightgray;
 ]]>
 </string>
 */
static const QString READING_SHARED_COMMENT_SPLIT =
    //" <![CDATA["
    "border-top:1px dotted lightgray;";
    //"]]>";

/**
 *     <string name="reading__shared__note">
 <![CDATA[
 <div style=\"font-size:11pt; margin-top:0.2em;\">
 <span style=\"font-weight:bold;\">注: </span>
 <span style=\"color:#888888\">%s</span>
 </div>
 ]]>
 </string>
 */
static const QString READING_SHARED_NOTE =
    //" <![CDATA["
    "<div style=\"font-size:11pt; margin-top:0.2em;\">"
    "<span style=\"font-weight:bold;\">Comment: </span>"
    "<span style=\"color:#888888\">%1</span>"
    "</div>";
    //"]]>";

/**
 *    <string name="reading__shared__foot">
 <![CDATA[
 <div style=\"margin-top:2em; margin-bottom:1em\">
 <hr style=\"height:2px; border:0; background-color:#ddd;\"/>
 <span style=\"font-size:10pt; color:gray;\">多看笔记 来自多看阅读 for Android</span>
 </div>
 </div>
 </div>
 <div style=\"width:90%%; max-width:600px;text-align:right;margin-top:-37px;margin-right:auto;margin-left:auto;color:#EEEEEE;font-size:10px\">duokanbookid:%s</div>
 ]]>
 </string>
 */
static const QString READING_SHARED_FOOT =
    //"<![CDATA["
    "<div style=\"margin-top:2em; margin-bottom:1em\">"
    "<hr style=\"height:2px; border:0; background-color:#ddd;\"/>"
    "<span style=\"font-size:10pt; color:gray;\">Duokan Notes From Duokan for Kindle</span>"
    "</div>"
    "</div>"
    "</div>"
    "<div style=\"width:90%%; max-width:600px;text-align:right;margin-top:-37px;margin-right:auto;margin-left:auto;color:#EEEEEE;font-size:10px\">duokanbookid:%1</div>";
    //"]]>";

EvernoteManager::EvernoteManager()
{

}

EvernoteManager::~EvernoteManager()
{
}
 
bool EvernoteManager::openSession(const QString& host, int port)
{
    session_.reset(new EvernoteSession(host, port));
    return true;
}

bool EvernoteManager::exportNote(const EvernoteContent& note)
{
    // prepare content
    QString title;
    QString content;
    if (!prepareContent(note, title, content))
    {
        return false;
    }
    
    // open note store
    NoteStorePtr note_store = session_->noteStoreClient();
    if (note_store == 0)
    {
        return false;
    }
    if (!EvernoteSession::openNoteStore(note_store))
    {
        return false;
    }
    
    // note book
    Notebook duokan_book;
    if (!makeSureNotebookExist(note_store, duokan_book))
    {
        return false;
    }
    
    // find metadata
    NotesMetadataList metadata;
    if (!findMetadata(note_store, note.book_id, duokan_book, metadata))
    {
        return false;
    }
    
    // send note
    bool ret = addOrUpdateNote(note_store, duokan_book, metadata, title, content);
    
    // close note store
    EvernoteSession::closeNoteStore(note_store);
    return ret;
}
    
bool EvernoteManager::prepareContent(const EvernoteContent& origin_content, QString& title, QString& content)
{
    // header
    QString content_str = makeHeader(origin_content.title, origin_content.author);
    
    // make each annotation
    bool border = false;
    foreach(const QString& chapter, origin_content.chapters)
    {
        QString chapter_title = QString(READING_SHARED_CHAPTER).arg(chapter);
        content_str += chapter_title;
        
        // draw border for each chapter
        border = true;
        QList<KindleAnnotationItem> annotations_in_chapter = origin_content.annotations.values(chapter);
        int count = 0;
        foreach(const KindleAnnotationItem& item, annotations_in_chapter)
        {
            count++;
            if (count == annotations_in_chapter.size())
            {
                border = false;
            }
            QString date = item.formattedDate();
            
            // TODO. use real color instead of const grey
            QString color = QString("%1,%2,%3").arg(100).arg(100).arg(100);
            QString note_text = item.content;
            QString note_comment = item.comment;
            
            QString annotation_content = QString(READING_SHARED_COMMENT)
            .arg(border ? READING_SHARED_COMMENT_SPLIT : "")
            .arg(color)
            .arg(date)
            .arg(replaceInvalidCharacters(note_text))
            .arg(note_comment.isEmpty() ? "" : QString(READING_SHARED_NOTE).arg(replaceInvalidCharacters(note_comment)));
            content_str += annotation_content;
        }
    }
    
    QString foot = QString(READING_SHARED_FOOT).arg(origin_content.book_id);
    content_str += foot;
    
    // return value
    title = origin_content.title;
    content = content_str;
    return true;
}
    
QString EvernoteManager::makeHeader(const QString& book_name, const QString& author)
{
    QString header = READING_SHARED_TITLE + book_name + READING_SHARED_TITLE_SUFFIX;
    if (!author.isEmpty())
    {
        QString author_str = QString(READING_SHARED_AUTHOR).arg(author);
        header = header.append(author_str);
    }
    return header;
}
    
bool EvernoteManager::makeSureNotebookExist(NoteStorePtr note_store, Notebook& duokan_book)
{
    // NOTE: note store should be opened before calling these functions
    QString duokan_book_name = QApplication::tr("Duokan Notebook");

    bool ret = true;
    // Find existing notebook
    Notebooks notebooks;
    try {
        note_store->listNotebooks(notebooks, session_->token().toStdString());
        foreach(const Notebook& book, notebooks)
        {
            QString book_name(book.name.c_str());
            if (book_name.compare(duokan_book_name) == 0)
            {
                duokan_book = book;
            }
        }
        
        // Create a new notebook if not exist
        if (duokan_book.name.empty())
        {
            Notebook new_book;
            new_book.name = duokan_book_name.toStdString();
            new_book.__isset.name = true;
            note_store->createNotebook(duokan_book, session_->token().toStdString(), new_book);
        }
    } catch(apache::thrift::TException te) {
        qDebug() << "TException:" << te.what() << "|" <<endl;
        ret = false;
    } catch(std::exception e) {
        qDebug() << "Error:" <<e.what() << "|" <<endl;
        ret = false;
    } catch(...) {
        qDebug() << "Error:unknown error" <<endl;
        ret = false;
    }
    return ret;
}
    
bool EvernoteManager::findMetadata(NoteStorePtr note_store,
                                const QString& book_id,
                                const Notebook& duokan_book,
                                NotesMetadataList& note_metadata)
{
    NoteFilter filter;
    filter.notebookGuid = duokan_book.guid;
    QString words_str = QString("duokanbookid:%1").arg(book_id);
    filter.words = words_str.toStdString();
    NotesMetadataResultSpec metadata_result_spec;
    bool ret = true;
    try {
        note_store->findNotesMetadata(note_metadata,
                                   session_->token().toStdString(),
                                   filter,
                                   0,
                                   1,
                                   metadata_result_spec);
    } catch(apache::thrift::TException te) {
        qDebug() << "TException:" << te.what() << "|" <<endl;
        ret = false;
    } catch(std::exception e) {
        qDebug() << "Error:" <<e.what() << "|" <<endl;
        ret = false;
    } catch(...) {
        qDebug() << "Error:unknown error" <<endl;
        ret = false;
    }
    return ret;
}
    
bool EvernoteManager::addOrUpdateNote(NoteStorePtr note_store,
                                   const Notebook& duokan_book,
                                   const NotesMetadataList& note_metadata,
                                   QString title,
                                   const QString& content)
{
    QString duokan_book_tag = QApplication::tr("Duokan Reading Notes");
    
    Note new_note;
    // guid
    new_note.notebookGuid = duokan_book.guid;
    new_note.__isset.notebookGuid = true;
    
    // tag names
    new_note.tagNames.push_back(duokan_book_tag.toStdString());
    new_note.__isset.tagNames = true;
    
    // title
    QString valid_title = title.replace(QRegExp("\\p{Cc}\\p{Zl}\\p{Zp}"), "");
    if (valid_title.length() > 255)
    {
        valid_title = valid_title.left(255);
    }
    new_note.title = valid_title.toStdString();
    new_note.__isset.title = true;
    
    // content
    QString submit_content = NOTE_PREFIX + content + NOTE_SUFFIX;
    new_note.content = submit_content.toStdString();
    
    // TEST
    //new_note.content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\"><en-note><span>this is a  another hello test to evernote api.</span> </en-note>";

    new_note.__isset.content = true;
    
    Note ret_note;
    bool ret = true;
    try
    {
        if (note_metadata.totalNotes == 0 ||
            (note_metadata.notes[0].title.empty() &&
             note_metadata.notes[0].contentLength == 0))
        {
            // not found existing note for the same book,
            // create a new note
            note_store->createNote(ret_note,
                                   session_->token().toStdString(),
                                   new_note);
            qDebug("Creating new note...");
        }
        else
        {
            // the note for this book exists, update it
            new_note.guid = note_metadata.notes[0].guid;
            note_store->updateNote(ret_note,
                                   session_->token().toStdString(),
                                   new_note);
            qDebug("Update note...");
        }
    } catch(apache::thrift::TException te) {
        qDebug() << "TException:" << te.what() << "|" <<endl;
        ret = false;
    } catch(std::exception e) {
        qDebug() << "Error:" <<e.what() << "|" <<endl;
        ret = false;
    } catch(...) {
        qDebug() << "Error:unknown error" <<endl;
        ret = false;
    }
    return ret;
}

}
