#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

typedef struct {
    long x, y;
} Tile;

// stores a vertical edge in this shape
typedef struct Edge {
    Tile start;
    long length;
} Edge;

Tile tiles[500];
int numTiles = 0;

Edge vertEdges[500];
int numVertEdges = 0;

Edge horizEdges[500];
int numHorizEdges = 0;

// abs uses ints, I use longs just in case
long absl(long a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

// for sort function
int compareVertEdges(const void *a, const void *b) {
    Edge arg1 = *(const Edge *)a;
    Edge arg2 = *(const Edge *)b;
    if (arg1.start.x > arg2.start.x) {
        return 1;
    }
    if (arg1.start.x < arg2.start.x) {
        return -1;
    }
    return 0;
}

// I always forget how the ternary operator goes, this is easier :)
long max(long a, long b) { if (a > b) return a; return b; }
long min(long a, long b) { if (a < b) return a; return b; }

int pointInRect(long top, long bottom, long left, long right, long x, long y) {
    return (y >= top && y <= bottom && x >= left && x <= right);
}

int pointInShape(long x, long y) {
    int topRay = 0;
    int bottomRay = 0;
    for (int i = 0; i < numVertEdges; i++) {
        Edge e = vertEdges[i];
        if (e.start.x > x) {
            return topRay || bottomRay;
        }
        if (y >= e.start.y && y < (e.start.y + e.length)) {
            // if the point is on an edge, it is always in the shape
            if (e.start.x == x) {
                return 1;
            }
            topRay = !topRay;
        }
        if (y > e.start.y && y <= (e.start.y + e.length)) {
            // if the point is on an edge, it is always in the shape
            if (e.start.x == x) {
                return 1;
            }
            bottomRay = !bottomRay;
        }
    }
    return topRay || bottomRay;
}

// checks if the rectangle defined by t1 and t2 is in the shape of red and green tiles
int rectInShape(Tile t1, Tile t2) {
    long top = min(t1.y, t2.y);
    long bottom = max(t1.y, t2.y);
    long left = min(t1.x, t2.x);
    long right = max(t1.x, t2.x);

    // for every tile
    for (int i = 0; i < numTiles; i++) {
        Tile t = tiles[i];
        // if the tile is in the rectangle
        // we check to see if all of the adjacent points that fit in the rectangle are in the shape
        if (pointInRect(top, bottom, left, right, t.x, t.y)) {
            for (int yo = -1; yo <= 1; yo++) {
                for (int xo = -1; xo <= 1; xo++) {
                    if (pointInRect(top, bottom, left, right, t.x+xo, t.y+yo) && !pointInShape(t.x+xo, t.y+yo)) {
                        return 0;
                    }
                }
            }
        }
    }
    // check to see if there are any overlapping edges
    for (int i = 0; i < numVertEdges; i++) {
        Edge e = vertEdges[i];
        if (e.start.x > left && e.start.x < right) {
            if (e.start.y < top && e.start.y + e.length > bottom) {
                return 0;
            }
        }
    }
    for (int i = 0; i < numHorizEdges; i++) {
        Edge e = horizEdges[i];
        if (e.start.y > top && e.start.y < bottom) {
            if (e.start.x < left && e.start.x + e.length > right) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long maxSize = 0;

    for (int i = 0; !feof(f); i++) {
        fscanf(f, "%ld,%ld ", &tiles[i].x, &tiles[i].y);
        numTiles ++;
    }

    // crawl shape and mark edges
    Tile prev = tiles[numTiles-1];
    for (int i = 0; i < numTiles; i++) {
        if (tiles[i].x == prev.x) {
            Tile start;
            long length;
            if (tiles[i].y < prev.y) {
                start = tiles[i];
            } else {
                start = prev;
            }
            length = absl(tiles[i].y - prev.y);
            vertEdges[numVertEdges] = (Edge){start, length};
            numVertEdges ++;
        }
        else {
            Tile start;
            long length;
            if (tiles[i].x < prev.x) {
                start = tiles[i];
            } else {
                start = prev;
            }
            length = absl(tiles[i].x - prev.x);
            horizEdges[numHorizEdges] = (Edge){start, length};
            numHorizEdges ++;
        }
        prev = tiles[i];
    }

    qsort(vertEdges, numVertEdges, sizeof(Edge), compareVertEdges);

    for (int i = 0; i < numTiles; i++) {
        for (int j = 0; j < numTiles; j++) {
            long size = (absl(tiles[i].x-tiles[j].x)+1) * (absl(tiles[i].y-tiles[j].y)+1);
            if (rectInShape(tiles[i], tiles[j])) {
                maxSize = max(maxSize, size);
            }
        }
    }

    printf("\n%ld\n", maxSize);

    return 0;
}