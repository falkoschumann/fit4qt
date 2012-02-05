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

#include "filerunner.h"

#include "fixture.h"
#include "parse.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include <iostream>

namespace Fit {

FileRunner::FileRunner(QObject *parent) :
    QObject(parent),
    fixture(new Fixture(this))
{
}

int FileRunner::run(int argc, char *argv[])
{
    if (!args(argc, argv)) return -1;
    process();
    return exit();
}

int FileRunner::args(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "usage: fit input-file output-file" << std::endl;
        return -1;
    }

    QFile in(argv[1]);
    QFile *out = new QFile(argv[2]);
    QFileInfo inFileInfo(in);
    QFileInfo outFileInfo(*out);
    fixture->summary["input file"] = inFileInfo.absoluteFilePath();
    fixture->summary["input update"] = inFileInfo.lastModified();
    fixture->summary["output file"] = outFileInfo.absoluteFilePath();

    if (!in.open(QIODevice::ReadOnly)) {
        std::cerr << "Can not open input file for reading: "
                  << qPrintable(in.errorString())
                  << std::endl;
        return -1;
    }
    input = in.readAll();

    if (!out->open(QIODevice::WriteOnly)) {
        std::cerr << "Can not open input file for writing: "
                  << qPrintable(out->errorString())
                  << std::endl;
        return -1;
    }
    output.setDevice(out);
}

void FileRunner::process()
{
    QStringList tags;
    tags << "table" << "tr" << "td";
    tables = new Parse(input, tags);
    fixture->doTables(tables);

    tables->print(output);
}

int FileRunner::exit()
{
    //output.flush();
    std::cerr << fixture->counts.toString().toStdString() << std::endl;
    return fixture->counts.wrong + fixture->counts.exceptions;
}

} // namespace Fit
