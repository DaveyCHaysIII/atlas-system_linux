#include <Python.h>
#include <stdio.h>

/**
 * print_python_list - prints a python list
 * @p: the list object in question
 *
 * Return: no return
 */

void print_python_list(PyObject *p)
{
	PyListObject *list = NULL;
	PyObject *member = NULL;
	Py_ssize_t length, allocated, i;
	const char *type_name = NULL;

	length = PyList_Size(p);

	if (PyList_Check(p))
	{
		list = (PyListObject *)p;
		allocated = list->allocated;

		printf("[*] Python list info\n"
			"[*] Size of the python list: %ld\n"
			"[*] Allocated = %ld\n",
			length, allocated);
		for (i = 0; i < length; i++)
		{
			member = list->ob_item[i];
			type_name = member->ob_type->tp_name;
			printf("Element %ld: %s\n", i, type_name);
		}
	}
	else
		return;
}
