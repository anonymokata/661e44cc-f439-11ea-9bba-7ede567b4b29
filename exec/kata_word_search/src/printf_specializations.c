// 3rdParty Includes
#include "kirke/error.h"
#include "kirke/string.h"

// Internal Includes
#include "word_search/grid.h"
#include "word_search/solution.h"

#include "printf_specializations.h"

static int array__string__arginfo( const struct printf_info *info, size_t n, int *argtypes, int *size ){
    (void) ( info );

    if( n > 0 ){
        argtypes[ 0 ] = PA_POINTER;
        size[ 0 ] = sizeof( Array__String );
    }
    
    return 1;
}

static int array__string__print( FILE *stream, const struct printf_info *info, const void *const *args ){
    (void) ( info );

    size_t bytes_written = 0;

    const Array__String* array = *( (const Array__String **) ( args[ 0 ] ) );

    for( unsigned long string_index = 0; string_index < array->length; string_index++ ){
        bytes_written += fwrite( 
            array->data[ string_index ].data, 
            array->data[ string_index ].length, 
            array->data[ string_index ].element_size, 
            stream 
        );

        if( string_index < array->length - 1 ){
            bytes_written += fprintf( stream, ", " );
        }
    }

    return bytes_written;
}

static int error__arginfo( const struct printf_info *info, size_t n, int *argtypes, int *size ){
    (void) ( info );

    if( n > 0 ){
        argtypes[ 0 ] = PA_POINTER;
        size[ 0 ] = sizeof( Error );
    }
    
    return 1;
}

static int error__print( FILE *stream, const struct printf_info *info, const void *const *args ){
    (void) ( info );

    size_t bytes_written = 0;

    const Error* error = *( (const Error **) ( args[ 0 ] ) );

    bytes_written += fprintf( stream, "Error:\n\t" );
    bytes_written += fprintf( stream, "Type: " );
    bytes_written += fwrite( error->type.data, 1, error->type.length, stream );
    bytes_written += fprintf( stream, "\n\tCode: %lu\n\t", error->code );
    bytes_written += fprintf( stream, "Message:\t" );
    bytes_written += fwrite( error->message.data, 1, error->message.length, stream );

    return bytes_written;
}

static int word_search__grid__arginfo( const struct printf_info *info, size_t n, int *argtypes, int *size ){
    (void) ( info );

    if( n > 0 ){
        argtypes[ 0 ] = PA_POINTER;
        size[ 0 ] = sizeof( WordSearch__Grid );
    }
    
    return 1;
}

static int word_search__grid__print( FILE *stream, const struct printf_info *info, const void *const *args ){
    (void) ( info );

    size_t bytes_written = 0;

    const WordSearch__Grid *grid = *( (const WordSearch__Grid **) ( args[ 0 ] ) );

    for( long row_index = 0; row_index < grid->height; row_index++ ){
        for( long column_index = 0; column_index < grid->width; column_index++ ){
            bytes_written += fprintf( stream, "%c", grid->entries.data[ ( row_index * grid->width ) + column_index ] );

            if( column_index < grid->width - 1 ){
                bytes_written += fprintf( stream, ", " );
            }
            else{
                bytes_written += fprintf( stream, "\n" );
            }
        }
    }

    return bytes_written;
}

static int word_search__solution__arginfo( const struct printf_info *info, size_t n, int *argtypes, int *size ){
    (void) ( info );

    if( n > 0 ){
        argtypes[ 0 ] = PA_POINTER;
        size[ 0 ] = sizeof( WordSearch__Solution );
    }
    
    return 1;
}

static int word_search__solution__print( FILE *stream, const struct printf_info *info, const void *const *args ){
    (void) ( info );

    size_t bytes_written = 0;

    const WordSearch__Solution *solution = *( (const WordSearch__Solution **) ( args[ 0 ] ) );

    bytes_written += fwrite( solution->word.data, solution->word.length, solution->word.element_size, stream );
    bytes_written += fprintf( stream, ":\t" );

    if( solution->disposition == WordSearch__Solution__Disposition__Found ){
        WordSearch__GridCoordinates entry_coordinates;
        for( 
            unsigned long long entry_index = 0; 
            word_search__grid_sequence__coordinates_of( &solution->sequence, entry_index, &entry_coordinates );
            entry_index++
        ){
            bytes_written += fprintf( stream, "( %ld, %ld )", entry_coordinates.column, entry_coordinates.row );
        
            if( entry_index < solution->sequence.span.magnitude - 1 ){
                bytes_written += fprintf( stream, ", " );
            }
        }
    }
    else{
        bytes_written += fprintf( stream, "NOT FOUND" );
    }


    return bytes_written;
}

static int string__arginfo( const struct printf_info *info, size_t n, int *argtypes, int *size ){
    (void) ( info );

    if( n > 0 ){
        argtypes[ 0 ] = PA_POINTER;
        size[ 0 ] = sizeof( String );
    }
    
    return 1;
}

static int string__print( FILE *stream, const struct printf_info *info, const void *const *args ){
    (void) ( info );

    const String* string = *( (const String **) ( args[ 0 ] ) );
    fwrite( string->data, string->length, string->element_size, stream );

    return string->length;
}

void printf_specializations__register( void ){
    register_printf_specifier( 'A', array__string__print, array__string__arginfo );
    register_printf_specifier( 'R', error__print, error__arginfo );
    register_printf_specifier( 'G', word_search__grid__print, word_search__grid__arginfo );
    register_printf_specifier( 'K', word_search__solution__print, word_search__solution__arginfo );
    register_printf_specifier( 'S', string__print, string__arginfo );
}
