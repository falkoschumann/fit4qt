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

#ifndef FIT_PARSE_H
#define FIT_PARSE_H

#include "fitexcept.h"

#include <QtCore/QStringList>

class QTextStream;

namespace Fit {

class Parse
{
public:
    QString leader;
    QString tag;
    QString body;
    QString end;
    QString trailer;

    Parse *parts;
    Parse *more;

    Parse(const QString &tag, const QString &body, Parse *parts = 0, Parse *more = 0);

    static QStringList tags;

    Parse(const QString &text,
          const QStringList &tags = Parse::tags,
          int level = 0,
          int offset = 0) throw (muspellheim::parse_exception);
    ~Parse();
    Parse* leaf();
    Parse* at(int i);
    Parse* at(int i, int j);
    Parse* at(int i, int j, int k);
    QString text();
    static QString htmlToText(QString s);
    static QString unescape(QString s);
    static QString condenseWhitespace(QString s);
    void addToTag(const QString &text);
    void addToBody(const QString &text);
    void print(QTextStream &out);


protected:
    static int findMatchingEndTag(const QString &lc,
                                  int matchFromHere,
                                  const QString &tag,
                                  int offset);

private:
    static QString removeNonBreakTags(QString s);
    static QString unescapeSmartQuotes(QString s);
    static QString unescapeEntities(QString s);
    static QString normalizeLineBreaks(QString s);
};

} // namespace Fit

#endif // FIT_PARSE_H
