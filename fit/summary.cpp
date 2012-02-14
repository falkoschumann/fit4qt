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

#include "summary.h"

#include "parse.h"

#include <QtCore/QDebug>

namespace Fit {

const QString Summary::countsKey("counts");

Summary::Summary(QObject *parent) :
    Fit::Fixture(parent)
{
}

void Summary::doTable(Parse *table)
{
    summary->insert(countsKey, counts->toString());
    QListIterator<QString> keys(summary->keys());
    table->parts->more = rows(keys);
}

Parse* Summary::rows(QListIterator<QString> &keys)
{
    if (keys.hasNext()) {
        QString key(keys.next());
        qDebug() << "key =" << key;
        Parse *result = tr(td(key, td(summary->value(key).toString(), 0)), rows(keys));
        if (key == countsKey)
            mark(result);
        return result;
    } else {
        return 0;
    }
}

Parse* Summary::tr(Parse *parts, Parse *more)
{
    return new Parse("tr", 0, parts, more);
}

Parse* Summary::td(const QString &body, Parse *more)
{
    return new Parse("td", info(body), 0, more);
}

void Summary::mark(Parse *row)
{
    // mark summary good/bad without counting beyond here
    Counts *official = new Counts(*counts);
    counts = new Counts();
    Parse *cell = row->parts->more;
    if (official->wrong + official->exceptions > 0) {
        wrong(cell);
    } else {
        right(cell);
    }
    counts = official;
}

} // namespace Fit
