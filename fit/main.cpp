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
#include "parseexception.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <iostream>

using namespace Fit;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: fit input-file output-file\n");
        return -1;
    }

    QString inputFilename(argv[1]);
    std::cout << "input file: " << inputFilename.toStdString() << std::endl;

    QString outputFilename(argv[2]);
    std::cout << "output file: " << outputFilename.toStdString() << std::endl;

    QFile inputFile(inputFilename);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        std::cerr << "Can not open input file for reading: "
                  << qPrintable(inputFile.errorString())
                  << std::endl;
        return -1;
    }

    QTextStream in(&inputFile);
    QString input = in.readAll();

    QStringList tags;
    tags << "table";
    try {
        Parse parse(input, tags);

        QFile outputFile(outputFilename);
        if (!outputFile.open(QIODevice::WriteOnly)) {
            std::cerr << "Can not open input file for writing: "
                      << qPrintable(inputFile.errorString())
                      << std::endl;
            return -1;
        }
        QTextStream out(&outputFile);
        parse.print(out);
    } catch (const ParseException &ex) {
        std::cout << "error: " << ex.message().toStdString() << std::endl;
        return -1;
    }

    return 0;
}
