#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

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

	if (!PyList_Check(p))
	{
		printf("[*] Python list info\n");
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	length = PyObject_Length(p);
	list = (PyListObject *)p;
	allocated = list->allocated;

	printf("[*] Python list info\n"
		"[*] Size of the Python List = %ld\n"
		"[*] Allocated = %ld\n",
		length, allocated);
	for (i = 0; i < length; i++)
	{
		member = list->ob_item[i];
		type_name = member->ob_type->tp_name;
		printf("Element %ld: %s\n", i, type_name);
		if (PyBytes_Check(member))
		{
			print_python_bytes(member);
		}
		if (PyFloat_Check(member))
		{
			print_python_float(member);
		}
	}

}

/**
 * print_python_bytes - prints the bytes
 * @p: the list object in question
 *
 * return: no return
 */

void print_python_bytes(PyObject *p)
{
	PyBytesObject *each_byte = NULL;
	Py_ssize_t size = 0;
	Py_ssize_t size_print = 0;
	Py_ssize_t i = 0;

	if (!p || !PyBytes_Check(p))
	{
		printf("[.] bytes object info\n"
				"  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = PyBytes_Size(p);
	each_byte = (PyBytesObject *)(p);

	if (size < 10)
	{
		size_print = size + 1;
	}
	else
	{
		size_print = 10;
	}

	printf("[.] bytes object info\n"
			"  size: %ld\n"
			"  trying string: %s\n"
			"  first %ld bytes:",
			size, each_byte->ob_sval,  size_print);

	for (i = 0; i < size_print; i++)
	{

		printf(" %02x", each_byte->ob_sval[i] & 0xff);
	}
	putchar('\n');
}


/**
 * print_python_float - prints a python float
 * @p: the object in question
 *
 * Return: no return
 */

void print_python_float(PyObject *p)
{
	if (!p || !PyFloat_Check(p))
	{
		printf("[.] float object info\n"
				"  [ERROR] Invalid Float Object\n");
		return;
	}

	PyFloatObject *floatie = NULL;
	char *float_string = NULL;

	printf("[.] float object info\n");

	floatie = (PyFloatObject *)(p);
	float_string = PyOS_double_to_string(floatie->ob_fval, 'g', 16, 0, NULL);
	printf("  value: %s%s\n",
			float_string, strchr(float_string, '.') ? "" : ".0");
}
