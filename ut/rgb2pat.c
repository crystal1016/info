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

#include "debug.h"
#include "image.h"

int main( int argc, char *argv[] ) {
    int width, height;
    IMAGE *in;

    if( argc != 4 ) {
        printf( "rgb2pat v" VERSION "\n"
                        "Author: Steve Slaven - http://hoopajoo.net\n"
                        "\n"
                        "usage: %s infile width height\n"
                        "\n"
                        "infile is an 24-bit RGB file of width/height\n"
                        "the resulting .pat file is written to stdout\n"
                        "\n"
                        "The file can be used with visgrep to scrape screen content\n"
                        "\n"
                        , argv[ 0 ] );

        exit( 1 );
    }

    sscanf( argv[ 2 ], "%d", &width );
    sscanf( argv[ 3 ], "%d", &height );

    dmsg( 1, "Reading image...\n" );
    in = img_load_from_rgb( argv[ 1 ], width, height );
    if( ! in ) {
        printf( "Failed to load %s\n", argv[ 1 ] );
        exit( 1 );
    }

    dmsg( 1, "Image attribs: %dx%d\n", in -> width, in -> height );
    dmsg( 1, "Writing image to img.out...\n" );
    img_write_fd( in, stdout );
    img_destroy( in );

    exit( 0 );
}
