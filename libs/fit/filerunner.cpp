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

#include <QtCore>

#include <stdexcept>

namespace Fit {

FileRunner::FileRunner(QObject *parent) :
    QObject(parent),
    fixture(new Fixture(this))
{
}

void FileRunner::run(int argc, char *argv[])
{
    args(argc, argv);
    process();
    exit();
}

void FileRunner::process()
{
    try {
        if (input.indexOf("<wiki>") >= 0) {
            tables = new Parse(input, QStringList() << "wiki" << "table" << "tr" << "td");
            fixture->doTables(tables->parts);
        } else {
            tables = new Parse(input, QStringList() << "table" << "tr" << "td");
            fixture->doTables(tables);
        }
    } catch (const std::exception &e) {
        exception(e);
    }
    tables->print(output);
}

void FileRunner::args(int argc, char *argv[])
{
    if (argc != 3) {
        qCritical() << "usage: fit input-file output-file";
        qApp->exit(-1);
    }

    QFile *in = new QFile(argv[1]);
    QFileInfo inInfo(*in);
    fixture->summary.insert("input file", inInfo.absoluteFilePath());
    fixture->summary.insert("input update", inInfo.lastModified());
    QFile *out = new QFile(argv[2]);
    QFileInfo outInfo(*out);
    fixture->summary.insert("output file", outInfo.absoluteFilePath());

    input = read(in);
    out->open(QIODevice::WriteOnly);
    output.setDevice(out);
}

QString FileRunner::read(QFile *input)
{
    if (!input->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString msg = QString("%1: %2").arg(input->fileName()).arg(input->errorString());
        throw std::logic_error(msg.toStdString());
    }
    return input->readAll();
}

void FileRunner::exception(const std::exception &e)
{
    tables = new Parse("body", "Unable to parse input. Input ignored.");
    fixture->exception(tables, e);
}

int FileRunner::exit()
{
    qCritical() << fixture->counts.toString();
    return fixture->counts.wrong + fixture->counts.exceptions;
}

} // namespace Fit
