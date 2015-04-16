/*
 *  
 *  Copyright (c) 2002 Steve Slaven, All Rights Reserved.
 *  
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA 02111-1307 USA
 *  
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "image.h"
#include "debug.h"

void do_output( int show_badness, int badness, int x, int y, int idx ) {
    if( show_badness ) {
        printf( "%d %d,%d %d\n", badness, x, y, idx );
    }else{
        printf( "%d,%d %d\n", x, y, idx );
    }
}

int main( int argc, char *argv[] ) {
    IMAGE *img;
    IMAGE *find;
    int off_x, off_y, tolerance;
    int start_x, start_y;
    int total_match;
    int show_badness = 0;
    int scan_all = 0;
    IMAGE **matches;

    POINT tmp_pt;
    FIND_RESULT pt;

    int cnt, gotmatch, tmp_i, find_next, final_exit;
    int tmp_off_x, tmp_off_y, sub_width, sub_height;
    int opt;

    off_x = off_y = sub_width = sub_height = 0;
    start_x = start_y = 0;
    tolerance = 0;
    final_exit = 1;

    while( ( opt = getopt( argc, argv, "hX:Y:x:d:y:t:baW:H:" ) ) != EOF ) {
        switch( opt ) {
        case 'h':
            printf( "visgrep v" VERSION "\n"
                        "visual grep, greps for images in another image\n"
                        "Author: Steve Slaven - http://hoopajoo.net\n"
                        "\n"
                        "usage: %s [-hba] [-x x_off] [-y y_off]\n"
                        "          [-w x_off_width] [-h y_off_height]\n"
                        "          [-X start x_off] [-Y start y_off]\n"
                        "          [-d debuglevel] [-t tolerance] image.png detect.png match.png ...\n"
                        "\n"
                        "  -h   This help\n"
                        "  -x   Set x offset for detection matching\n"
                        "  -y   Set y offset for detection matching\n"
                        "  -W   Set x offset width for detection matching\n"
                        "  -H   Set y offset height for detection matching\n"
                        "  -X   Start scanning at X\n"
                        "  -Y   Start scanning at Y\n"
                        "  -a   Scan all patterns, not just after matching the detection pattern\n"
                        "       note: this method is much slower because we scan for all images\n"
                        "             at every pixel instead of just at detection points.  Also,\n"
                        "             in this mode the detection image is ignored, there will be\n"
                        "             no matches for tile -1\n"
                        "  -t   Set tolerance for 'fuzzy' matches, higher numbers are more tolerant\n"
                        "  -b   Display 'badness' value, higher numbers mean match is less accurate,\n"
                        "       a badness value of 0 means the match is pixel-perfect\n"
                        "\n"
                        "The detect.png and match.png can also be .pat files.\n"
                        "\n"
                        "All .pat files are created using png2pat or rgb2pat.  The image.png is\n"
                        "scanned for detect.pat starting from X,Y specified above.  When detect.pat\n"
                        "is found, then all the match.pat files are scanned at an offset of x,y as\n"
                        "specified above.  If a match is found, then visgrep prints the x,y and\n"
                        "index of the item.\n"
                        "\n"
                        "image.png must be an 8 bit deep RGB or RGBA png file."
                        "\n"
                        "For example, image.png is a screenshot and match1.pat .. to match5.pat are\n"
                        "images of letters a to e.  Each of these letters is enclosed in a blue box,\n"
                        "so detect.pat is an image of the upper left corner of the box.  This box is\n"
                        "not included in the match*.pat files, so they are actually offset 5 pixels\n"
                        "down and 4 pixels to the left.  You might run it like this then:\n"
                        "\n"
                        "  visgrep -b -t50 -x-4 -y5 image.png match_corner.pat match_a.pat match_b.pat ...\n"
                        "\n"
                        "Etc, with all matches listed.  Now suppose the screen showed 'ace' so\n"
                        "visgrep might output:\n"
                        "\n"
                        "0 10,10 0\n"
                        "12 50,10 2\n"
                        "7 90,10 4\n"
                        "\n"
                        "Showing that match_a.pat (index 0) is at 10,10 on the screen.  If no match\n"
                        "is found even though the detection image is found, the index will be -1.\n"
                        "\n"
                        "The first match was 100\% accurate, while the second and third were very slightly\n"
                        "inaccurate, probably due to anti-aliasing on the fonts.\n"
                        "\n"
                        "Exit status is 0 for successful match, 1 for no match, and 2 for error.\n"
                        "\n"
                        "See the examples page for use cases for different flags\n"
                        , argv[ 0 ] );
            exit( 0 );
            break;

        case 'b':
            show_badness = 1;
            dmsg( 2, "Enable show_badness\n" );
            break;

        case 'a':
            scan_all = 1;
            dmsg( 2, "Enable scan_all\n" );
            break;

        case 'x':
            sscanf( optarg, "%d", &off_x );
            dmsg( 2, "X offset is %d\n", off_x );
            break;

        case 'y':
            sscanf( optarg, "%d", &off_y );
            dmsg( 2, "Y offset is %d\n", off_y );
            break;

        case 'X':
            sscanf( optarg, "%d", &start_x );
            dmsg( 2, "Start X offset is %d\n", start_x );
            break;

        case 'Y':
            sscanf( optarg, "%d", &start_y );
            dmsg( 2, "Start Y offset is %d\n", start_y );
            break;

        case 'W':
            sscanf( optarg, "%d", &sub_width );
            dmsg( 2, "Start x offset width %d\n", sub_width );
            break;

        case 'H':
            sscanf( optarg, "%d", &sub_height );
            dmsg( 2, "Start y offset height %d\n", sub_height );
            break;

        case 't':
            sscanf( optarg, "%d", &tolerance );
            dmsg( 2, "Tolerance is %d\n", tolerance );
            break;

        case 'd':
            sscanf( optarg, "%d", &tmp_i );
            dmsg( 2, "Debug set to %d\n", tmp_i );
            debug_level( tmp_i );
            break;

        case '?':
            fprintf( stderr, "Unknown option '%c'\n", optopt );
            break;

        default:
            fprintf( stderr, "Unhandled option '%c'\n", opt );
            break;
        }
    }

    if( argc - optind < 2 ) {
        fprintf( stderr, "Error, not enough args, try -h\n" );
        exit( 2 );
    }

    dmsg( 1, "Loading main PNG image '%s'\n", argv[ optind ] );
    img = img_load_from_png( argv[ optind ] );
    optind++;
    if( img == NULL ) {
        fprintf( stderr, "Error, unable to load png, try -h\n" );
        exit( 2 );
    }

    dmsg( 1, "Loading detection image '%s'\n", argv[ optind ] );
    find = img_load( argv[ optind ] );
    if( find == NULL ) {
        printf( "Error loading '%s'\n", argv[ optind ] );
        exit( 2 );
    }
    dmsg( 1, "Loaded %dx%d\n", find -> width, find -> height );
    optind++;

    total_match = argc - optind;
    dmsg( 1, "Now optind=%d : argc=%d : total_match=%d\n", optind, argc, total_match );

    matches = (IMAGE **)malloc( total_match * sizeof( IMAGE * ) );

    /* Load actual scoreboxes */
    dmsg( 1, "Loading match data....\n" );
    for( cnt = 0; cnt < total_match; cnt++ ) {
        dmsg( 1, " -- %s\n", argv[ optind ] );
        matches[ cnt ] = img_load( argv[ optind ] );
        if( matches[ cnt ] == NULL ) {
            printf( "Error loading '%s'\n", argv[ optind ] );
            exit( 2 );
        }
        optind++;
    }

    dmsg( 1, "Detecting offsets...\n" );
    pt.point.x = start_x;
    pt.point.y = start_y;
    find_next = 0;
    while( pt.point.x != -1 ) {
        if( scan_all ) {
            /* fake match here */
            if( find_next ) {
                /* increment counters */
                pt.point.x++;
                if( pt.point.x > img -> width ) {
                    pt.point.x = start_x;
                    pt.point.y++;
                    if( pt.point.y > img -> height ) {
                        /* done, bail */
                        pt.point.x = -1;
                        pt.point.y = -1;
                    }
                }
            }
        }else{
            pt = img_subimage_find( img, find, pt.point, tolerance, find_next );
        }

        /* Not first time anymore */
        find_next = 1;

        if( pt.point.x != -1 ) {
            dmsg( 1, "  Found match at %d,%d\n", pt.point.x, pt.point.y );

            /* Try and identify what thing it is */
            gotmatch = 0;
            for( tmp_off_x = 0; tmp_off_x < sub_width; tmp_off_x++ ) {
                for( tmp_off_y = 0; tmp_off_y < sub_height; tmp_off_y++ ) {
                    if( ! gotmatch ) {
                        tmp_pt.x = pt.point.x + off_x + tmp_off_x;
                        tmp_pt.y = pt.point.y + off_y + tmp_off_y;
                        for( cnt = 0; cnt < total_match; cnt++ ) {
                            if( matches[ cnt ] != NULL ) {
                                if( ! gotmatch ) {
                                    dmsg( 1, " Testing for %d  ", cnt );
                                    dmsg( 1, " (%d,%d) ", tmp_pt.x, tmp_pt.y );
                                    int badness = img_subimage_cmp( img, matches[ cnt ], tmp_pt, tolerance );
                                    if( badness <= tolerance ) {
                                        dmsg( 1, "  YES\n" );

                                        do_output( show_badness, badness, tmp_pt.x, tmp_pt.y, cnt );

                                        gotmatch = 1;
                                        final_exit = 0;

                                        /* Fall out */
                                        cnt = total_match;
                                    }else{
                                        dmsg( 1, "  NO\n" );
                                    }
                                }
                            }else{
                                dmsg( 1, " No image in slot %d\n", cnt );
                            }
                        }
                    }
                }
            }

            /* Notify of no match */
            if( ! gotmatch ) {
                dmsg( 1, " NO ITEMS MATCHED!\n" );
                if( ! scan_all ) {
                    do_output( show_badness, pt.badness, pt.point.x, pt.point.y, -1 );
                }
            }
        }
    }

    exit( final_exit );
}
