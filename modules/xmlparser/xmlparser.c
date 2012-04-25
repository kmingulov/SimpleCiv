
// comment
//
//

#include "xmlparser.h"


void xml_read_info(int type, FILE *file)
{
 // по fi определяем от куда читать
 //по type определяем тип структуры в какую записывать
 //создаем элемент структуры
 // дописываем в дерево


    //file = fopen("file.txt","r");

    if (file == NULL)
    {
        printf("Error");
    }


    fclose(file);


}
