/* Copyright (c) 2012; Falko Schumann, Muspellheim.de
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials  provided with the distribution.
 *  - Neither the name of the Muspellheim.de nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written  permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "parse.h"

#include <QtCore/QTextStream>

namespace Fit {

QStringList Parse::tags = (QStringList() << "table" << "tr" << "td");

Parse::Parse(const QString &text, const QStringList &tags, int level, int offset) throw (ParseException) :
    more(0),
    parts(0)
{
    QString lc = text.toLower();
    int startTag = lc.indexOf("<"+tags[level]);
    int endTag = lc.indexOf(">", startTag) + 1;
    //    int startEnd = lc.indexOf("</"+tags[level], endTag);
    int startEnd = findMatchingEndTag(lc, endTag, tags[level], offset);
    int endEnd = lc.indexOf(">", startEnd) + 1;
    int startMore = lc.indexOf("<"+tags[level], endEnd);
    if (startTag<0 || endTag<0 || startEnd<0 || endEnd<0) {
        throw ParseException("Can't find tag: "+tags[level], offset);
    }

    leader = text.mid(0, startTag);
    tag = text.mid(startTag, endTag-startTag);
    body = text.mid(endTag, startEnd-endTag);
    end = text.mid(startEnd, endEnd-startEnd);
    trailer = text.mid(endEnd);

    if (level+1 < tags.length()) {
        parts = new Parse(body, tags, level+1, offset+endTag);
        body = QString();
    }
    else { // Check for nested table
        int index = body.indexOf("<" + tags[0]);
        if (index >= 0) {
            parts = new Parse(body, tags, 0, offset + endTag);
            body = "";
        }
    }

    if (startMore>=0) {
        more = new Parse(trailer, tags, level, offset+endEnd);
        trailer = QString();
    }
}

Parse::~Parse()
{
    if (parts) {
        delete parts;
        parts = 0;
    }
    if (more) {
        delete more;
        more = 0;
    }
}

QString Parse::text()
{
    // TODO implement method stub
}

int Parse::findMatchingEndTag(const QString &lc, int matchFromHere, const QString &tag, int offset) throw (ParseException)
{
    int fromHere = matchFromHere;
    int count = 1;
    int startEnd = 0;
    while (count > 0) {
        int embeddedTag = lc.indexOf("<" + tag, fromHere);
        int embeddedTagEnd = lc.indexOf("</" + tag, fromHere);
        // Which one is closer?
        if (embeddedTag < 0 && embeddedTagEnd < 0)
            throw ParseException("Can't find tag: " + tag, offset);
        if (embeddedTag < 0)
            embeddedTag = INT_MAX;
        if (embeddedTagEnd < 0)
            embeddedTagEnd = INT_MAX;
        if (embeddedTag < embeddedTagEnd) {
            count++;
            startEnd = embeddedTag;
            fromHere = lc.indexOf(">", embeddedTag) + 1;
        }
        else if (embeddedTagEnd < embeddedTag) {
            count--;
            startEnd = embeddedTagEnd;
            fromHere = lc.indexOf(">", embeddedTagEnd) + 1;
        }
    }
    return startEnd;
}

void Parse::addToTag(const QString &text)
{
    int last = tag.length() - 1;
    tag = tag.mid(0, last) + text + ">";
}

void Parse::print(QTextStream &out)
{
    out << leader;
    out << tag;
    if (parts)
        parts->print(out);
    else
        out << body;
    out << end;
    if (more)
        more->print(out);
    else
        out << trailer;
}

} // namespace Fit
