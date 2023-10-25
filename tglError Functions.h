#ifndef TGL_ERROR_FUNCTIONS_H
    #define TGL_ERROR_FUNCTIONS_H



//{TGL::tglError functions

void TGL::DisplayError(size_t index, FILE *outputStream)
{
    if (index>TGL::errorCount)
    {
        printf("\n\n\n   Fatal Error in function \"TGL::DisplayError(size_t index, FILE *outputStream)\":\nArray out of bounds. Object index %u attempted to be accessed, but the last object's index is %u.\n\n\n",
               index,
               TGL::errorCount-1);
               //TGL::errorCount>0? TGL::errorCount-1:0);

        if (TGL::HandleError)
        {
            TGL::HandleError(TGL::arrayOutOfBounds);
        }
    }

    TGL::errorArray[index]->DisplayError(outputStream);
}

void TGL::DisplayLastError(FILE *outputStream)
{
    TGL::DisplayError(TGL::errorCount-1, outputStream);
}

void TGL::DisplayAllErrors(FILE *outputStream)
{
    for (size_t index=0; index<TGL::errorCount; index++)
    {
        TGL::DisplayError(index, outputStream);
    }
}

void TGL::ExportToFile(size_t index, const char *directory)
{
    if (index>TGL::errorCount)
    {
        printf("\n\n\n   Fatal Error in function \"TGL::ExportToFile(size_t index, const char *directory)\":\nArray out of bounds. Object index %u attempted to be accessed, but the last object's index is %u.\n\n\n",
               index,
               TGL::errorCount-1);
               //TGL::errorCount>0? TGL::errorCount-1:0);

        if (TGL::HandleError)
        {
            TGL::HandleError(TGL::arrayOutOfBounds);
        }
    }

    TGL::errorArray[index]->ExportToFile(directory);
}



void TGL::ErrorCombination000(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s",
            TGL::errorArray[index]->errorMessage());
}

void TGL::ErrorCombination001(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nVariable Address: %p",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->variableAddress());
}

void TGL::ErrorCombination010(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nVariable Name: %s",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->variableName());
}

void TGL::ErrorCombination011(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nVariable Name: %s\nVariable Address: %p",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->variableName(),
            TGL::errorArray[index]->variableAddress());
}

void TGL::ErrorCombination100(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nFunction Name: %s",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->functionName());
}

void TGL::ErrorCombination101(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nFunction Name: %s\nVariable Address: %p",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->functionName(),
            TGL::errorArray[index]->variableAddress());
}

void TGL::ErrorCombination110(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nFunction Name: %s\nVariable Name: %s",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->functionName(),
            TGL::errorArray[index]->variableName());
}

void TGL::ErrorCombination111(size_t index, FILE *outputStream)
{
    fprintf(outputStream,
            "%s\nFunction Name: %s\nVariable Name: %s\nVariable Address: %p",
            TGL::errorArray[index]->errorMessage(),
            TGL::errorArray[index]->functionName(),
            TGL::errorArray[index]->variableName(),
            TGL::errorArray[index]->variableAddress());
}

//}TGL::tglError functions



#endif // TGL_ERROR_FUNCTIONS_H






































