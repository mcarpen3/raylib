#include <raylib.h>
#include <stdio.h>
#include "../datastructs/linkedlist.h"

void DestroyRect(Rectangle *r) {
    free(r);
};

void GetSpriteBounds(Image img, List *rects) { 
    int minx;
    int yAlphaSum = 0;
    bool minxFound = false;
    for (int w = 0; w < img.width; ++w) {
        // iterate horizontally
        for (int h = 0; h < img.height; ++h) {
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
        for (int h = 0; h < img.height; ++h) {
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
    return rects;
}

int main(void) {
    List *rects = (List *)malloc(sizeof(List));
    list_init(rects, (void *)DestroyRect);
    InitWindow(1920, 1080, "AutoGetSpriteRect");
    Image img = LoadImage("/home/matt/Documents/c/raylib/spritesheets/knight/_WallClimb.png");
    GetSpriteBounds(img, rects);
    Texture2D texture = LoadTextureFromImage(img);
    ListElmt *el;
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTexture(texture, 0, 0, WHITE);
        el = list_head(rects);
        while(el != NULL) {
            Rectangle *r = (Rectangle *)el->data;
            DrawRectangleLinesEx(*r, 1.0f, GREEN);
            el = el->next;
        }
        EndDrawing();
    }
}