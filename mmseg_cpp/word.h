#ifndef _WORD_H_
#define _WORD_H_

#include <climits>
#include <cstring>

#include "memory.h"

namespace rmmseg
{
    const int word_embed_len = 4; /* at least 1 char (3 bytes+'\0') */
    struct Word
    {
        unsigned char   nbytes;   /* number of bytes */
        char            length;   /* number of characters */
        unsigned        freq;
        char            text[word_embed_len];
    };

    /**
     * text: the text of the word.
     * length: number of characters (not bytes).
     * freq: the frequency of the word.
     */
    inline Word *make_word(const char *text, int length=1,
                           unsigned freq=0, int nbytes=-1)
    {
        if (freq > UINT_MAX)
            freq = UINT_MAX;   /* avoid overflow */
        if (nbytes == -1)
            nbytes = strlen(text);
        Word *w = static_cast<Word *>(pool_alloc(sizeof(Word)
                                                 + nbytes+1
                                                 - word_embed_len));
        w->nbytes = std::strlen(text);
        w->length = length;
        w->freq = freq;
        std::strncpy(w->text, text, nbytes);
        w->text[nbytes] = '\0';
        return w;
    }
}

#endif /* _WORD_H_ */
