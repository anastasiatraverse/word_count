//
// Created by Анастасия Траверсе on 5/24/19.
//

#ifndef LAB_WORDS_UNZIP_H
#define LAB_WORDS_UNZIP_H
#include <archive.h>
#include <archive_entry.h>

static int copy_data(struct archive *ar, struct archive *aw);
static int extract(const char *filename);
#endif //LAB_WORDS_UNZIP_H
