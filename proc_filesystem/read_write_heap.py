#!/usr/bin/python3
"""Accessing active processes and altering their HEAP memory"""

import sys


def parse_args():
    """Check if the correct number of arguments is provided"""

    if len(sys.argv) != 4:
        print("Usage: read_write_heap.py pid search_string replace_string")
        sys.exit(1)

    pid = sys.argv[1]
    search_string = sys.argv[2]
    replace_string = sys.argv[3]

    return pid, search_string, replace_string


def find_heap_region(pid):
    """finds the region in the heap to parse through"""

    maps_file = f"/proc/{pid}/maps"

    try:
        with open(maps_file, "r") as f:
            for line in f:
                if "[heap]" in line:
                    address_range = line.split()[0]
                    start_addr, end_addr = address_range.split("-")

                    start_addr = int(start_addr, 16)
                    end_addr = int(end_addr, 16)

                    return start_addr, end_addr
        print(f"Could not find heap region for PID {pid}")
        sys.exit(1)

    except FileNotFoundError:
        print(f"Process with PID {pid} not found.")
        sys.exit(1)


def search_and_replace_in_heap(
                                pid,
                                heap_start,
                                heap_end,
                                search_string,
                                replace_string):
    """finds and replaces the string in heap memory"""

    mem_file = f"/proc/{pid}/mem"

    if len(search_string) != len(replace_string):
        print(
                "Error: search and replace string must be same length.")
        sys.exit(1)

    try:
        with open(mem_file, "rb+") as mem:

            mem.seek(heap_start)

            heap_size = heap_end - heap_start
            heap_data = mem.read(heap_size)

            search_bytes = search_string.encode('ascii')
            replace_bytes = replace_string.encode('ascii')
            offset = heap_data.find(search_bytes)

            if offset == -1:
                print(f"String '{search_string}' not found in heap.")
                return

            mem.seek(heap_start + offset)
            mem.write(replace_bytes)

            print(f"Replaced '{search_string}' "
                  f"with '{replace_string}' at offset {offset:#x}")

    except PermissionError:
        print(f"Permission denied. You might need to run the script as root.")
        sys.exit(1)
    except FileNotFoundError:
        print(f"Process with PID {pid} not found.")
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)


if __name__ == "__main__":
    pid, search_string, replace_string = parse_args()
    heap_start, heap_end = find_heap_region(pid)
    search_and_replace_in_heap(
                                pid,
                                heap_start,
                                heap_end,
                                search_string,
                                replace_string)
