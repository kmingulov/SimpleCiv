/*

    SimpleCiv is simple clone of Civilization game, using ncurses library.
    Copyright (C) 2012 by K. Mingulov, A. Sapronov.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef LIST_H
#define LIST_H

/*
    Struct of element of cycle list.
*/
typedef struct ListElement
{
    void * data;
    struct ListElement * next, * prev;
} ListElement;

/*
    Struct of list.
*/
typedef struct List
{
    int length;
    ListElement * head;
} List;

/*
    Creates list.
*/
List * listCreate();

/*
    Destroys list. Function is function for data deletion.
*/
void listDestroy(List * list, void (* function)(void * data));

/*
    Adds data to the end of the list (before head).
*/
void listPrepend(List * list, void * data);

/*
    Returns n-th (away from head) element.
*/
void * listGetByN(List * list, int n);

/*
    Returns list element, which contains data.
*/
ListElement * getListElementByPointer(List * list, void * data);

/*
    Removes element in list by pointer.
    Returns 0 if deleted succesfully, 1 if failed.
*/
int listDeleteByPointer(List * list, void * data, void (* function)(void * data));

/*
    Executes function for each list element.
*/
void listForEach(List * list, void (* function)(void * data));

#endif
