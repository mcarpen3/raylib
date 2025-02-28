#include <raylib.h>
#include <stdio.h>
#include "../sprite/sprite.h"
#include "../datastructs/linkedlist.h"

void GetSpriteBounds(SpriteRect *sprite, List *rects) {
    int minx;
    int yAlphaSum = 0;
    bool minxFound = false;
    Image img = LoadImageFromTexture(sprite->texture);
    for (int w = sprite->r.x; w < sprite->r.width; ++w) {
        // iterate horizontally
        for (int h = 0; h < sprite->r.height; ++h) {
            // iterate vertically
            Color c = GetImageColor(img, w, h);
            yAlphaSum += c.a;
        }
        if (yAlphaSum > 0 && !minxFound) {
            minx = w;
            minxFound = true;
        }
        if (yAlphaSum == 0 && minxFound) {
            Rectangle *r = (Rectangle *)malloc(sizeof(Rectangle));
            *r = (Rectangle){
                .x = minx,
                .y = 0,
                .width = w - minx - 1,
                .height = 0
            };
            list_ins_next(rects, list_tail(rects), r);
            minxFound = false;
        }
        yAlphaSum = 0;
    }
    ListElmt *idx = list_head(rects);
    while(idx != NULL) {
        int xAlphaSum = 0;
        bool minyFound = false;
        Rectangle *tmp = (Rectangle *)idx->data;
        for (int h = sprite->r.y; h < sprite->r.height; ++h) {
            for (int w = tmp->x; w < tmp->x + tmp->width; ++w) {
                Color c = GetImageColor(img, w, h);
                xAlphaSum += c.a;
            }
            if (xAlphaSum > 0 && !minyFound) {
                tmp->y = h;
                minyFound = true;
            }
            if (minyFound && (xAlphaSum == 0 || h == img.height - 1)) {
                tmp->height = h - tmp->y;
                break;
            }
            xAlphaSum = 0;
        }
        idx = idx->next;
    }
}