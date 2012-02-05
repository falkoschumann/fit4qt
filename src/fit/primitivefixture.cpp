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

#include "primitivefixture.h"

#include "parse.h"

#include <QtCore/QVariant>

namespace Fit {

long PrimitiveFixture::parseLong(Parse *cell)
{
    return QVariant(cell->text()).toLongLong();
}

double PrimitiveFixture::parseDouble(Parse *cell)
{
    return QVariant(cell->text()).toDouble();
}

bool PrimitiveFixture::parseBool(Parse *cell)
{
    return QVariant(cell->text()).toBool();
}

PrimitiveFixture::PrimitiveFixture(QObject *parent) :
    Fit::Fixture(parent)
{
}

void PrimitiveFixture::check(Parse *cell, const QString &value)
{
    if (cell->text() == value)
        right(cell);
    else
        wrong(cell, value);
}

void PrimitiveFixture::check(Parse *cell, long value)
{
    if (parseLong(cell) == value)
        right(cell);
    else
        wrong(cell, QString::number(value));
}

void PrimitiveFixture::check(Parse *cell, double value)
{
    if (parseDouble(cell) == value)
        right(cell);
    else
        wrong(cell, QString::number(value));
}

void PrimitiveFixture::check(Parse *cell, bool value)
{
    if (parseBool(cell) == value)
        right(cell);
    else
        wrong(cell, QString::number(value));
}

} // namespace Fit
