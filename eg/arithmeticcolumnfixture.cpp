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

#include "arithmeticcolumnfixture.h"

using namespace Fit;

namespace Eg {

ArithmeticColumnFixture::ArithmeticColumnFixture(QObject *parent) :
    Fit::ColumnFixture(parent)
{
}

int ArithmeticColumnFixture::x() const
{
    return m_x;
}

void ArithmeticColumnFixture::setX(int x)
{
    m_x = x;
}

int ArithmeticColumnFixture::y() const
{
    return m_y;
}

void ArithmeticColumnFixture::setY(int y)
{
    m_y = y;
}

int ArithmeticColumnFixture::plus() const
{
    return m_x + m_y;
}

int ArithmeticColumnFixture::minus() const
{
    return m_x - m_y;
}

int ArithmeticColumnFixture::times() const
{
    return m_x * m_y;
}

int ArithmeticColumnFixture::divide() const
{
    return m_x / m_y;
}

float ArithmeticColumnFixture::floating() const
{
    return (float)m_x / (float)m_y;
}

//ScientificDouble ArithmeticColumnFixture::sin() const
//{
//    return ScientificDouble(Math.sin(Math.toRadians(x)));
//}

//ScientificDouble ArithmeticColumnFixture::cos() const
//{
//    return ScientificDouble(Math.cos(Math.toRadians(x)));
//}

} // namespace Eg
