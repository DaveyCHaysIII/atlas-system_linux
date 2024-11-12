Readme!

remember to use swap funcs for all multi-byte integers


//from the elf Man page
String and symbol tables
       String table sections hold null-terminated character sequences,
       commonly called strings.  The object file uses these strings to
       represent symbol and section names.  One references a string as
       an index into the string table section.  The first byte, which is
       index zero, is defined to hold a null byte ('\0').  Similarly, a
       string table's last byte is defined to hold a null byte, ensuring
       null termination for all strings.

       An object file's symbol table holds information needed to locate
       and relocate a program's symbolic definitions and references.  A
       symbol table index is a subscript into this array.

           typedef struct {
               uint32_t      st_name;
               Elf32_Addr    st_value;
               uint32_t      st_size;
               unsigned char st_info;
               unsigned char st_other;
               uint16_t      st_shndx;
           } Elf32_Sym;

           typedef struct {
               uint32_t      st_name;
               unsigned char st_info;
               unsigned char st_other;
               uint16_t      st_shndx;
               Elf64_Addr    st_value;
               uint64_t      st_size;
           } Elf64_Sym;

       The 32-bit and 64-bit versions have the same members, just in a
       different order.

       st_name
              This member holds an index into the object file's symbol
              string table, which holds character representations of the
              symbol names.  If the value is nonzero, it represents a
              string table index that gives the symbol name.  Otherwise,
              the symbol has no name.

       st_value
              This member gives the value of the associated symbol.

       st_size
              Many symbols have associated sizes.  This member holds
              zero if the symbol has no size or an unknown size.

       st_info
              This member specifies the symbol's type and binding
              attributes:

              STT_NOTYPE (0)
                     The symbol's type is not defined.

              STT_OBJECT (1)
                     The symbol is associated with a data object.

              STT_FUNC (2)
                     The symbol is associated with a function or other
                     executable code.

              STT_SECTION (3)
                     The symbol is associated with a section.  Symbol
                     table entries of this type exist primarily for
                     relocation and normally have STB_LOCAL bindings.

              STT_FILE (4)
                     By convention, the symbol's name gives the name of
                     the source file associated with the object file.  A
                     file symbol has STB_LOCAL bindings, its section
                     index is SHN_ABS, and it precedes the other
                     STB_LOCAL symbols of the file, if it is present.

		(the following are from the elf.h file:
		#define STT_COMMON      5                Symbol is a common data object
		#define STT_TLS         6                Symbol is thread-local data object
		#define STT_NUM         7                Number of defined types.
		#define STT_LOOS        10               Start of OS-specific
		#define STT_GNU_IFUNC   10               Symbol is indirect code object
		#define STT_HIOS        12               End of OS-specific
		)

              STT_LOPROC (13)
              STT_HIPROC (15)
                     Values in the inclusive range [STT_LOPROC,
                     STT_HIPROC] are reserved for processor-specific
                     semantics.

              STB_LOCAL (0)
                     Local symbols are not visible outside the object
                     file containing their definition.  Local symbols of
                     the same name may exist in multiple files without
                     interfering with each other.

              STB_GLOBAL (1)
                     Global symbols are visible to all object files
                     being combined.  One file's definition of a global
                     symbol will satisfy another file's undefined
                     reference to the same symbol.

              STB_WEAK (2)
                     Weak symbols resemble global symbols, but their
                     definitions have lower precedence.

		(the following are from the elf.h file
		#define STB_NUM         3               /* Number of defined types.  */
		#define STB_LOOS        10              /* Start of OS-specific */
		#define STB_GNU_UNIQUE  10              /* Unique symbol.  */
		#define STB_HIOS        12              /* End of OS-specific */
		)

              STB_LOPROC (13)
              STB_HIPROC (15)
                     Values in the inclusive range [STB_LOPROC,
                     STB_HIPROC] are reserved for processor-specific
                     semantics.

              There are macros for packing and unpacking the binding and
              type fields:

              ELF32_ST_BIND(info)
              ELF64_ST_BIND(info)
                     Extract a binding from an st_info value.

              ELF32_ST_TYPE(info)
              ELF64_ST_TYPE(info)
                     Extract a type from an st_info value.

              ELF32_ST_INFO(bind, type)
              ELF64_ST_INFO(bind, type)
                     Convert a binding and a type into an st_info value.

       st_other
              This member defines the symbol visibility.

              STV_DEFAULT (0)
                     Default symbol visibility rules.  Global and weak
                     symbols are available to other modules; references
                     in the local module can be interposed by
                     definitions in other modules.
              STV_INTERNAL (1)
                     Processor-specific hidden class.
              STV_HIDDEN (2)
                     Symbol is unavailable to other modules; references
                     in the local module always resolve to the local
                     symbol (i.e., the symbol can't be interposed by
                     definitions in other modules).
              STV_PROTECTED (3)
                     Symbol is available to other modules, but
                     references in the local module always resolve to
                     the local symbol.

              There are macros for extracting the visibility type:

              ELF32_ST_VISIBILITY(other) or ELF64_ST_VISIBILITY(other)

       st_shndx
              Every symbol table entry is "defined" in relation to some
              section.  This member holds the relevant section header
              table index.

	#define SHN_UNDEF       0               /* Undefined section */
	#define SHN_LORESERVE   0xff00          /* Start of reserved indices */
	#define SHN_LOPROC      0xff00          /* Start of processor-specific */
	#define SHN_BEFORE      0xff00          /* Order section before all others
      		                                     (Solaris).  */
	#define SHN_AFTER       0xff01          /* Order section after all others
        	                                   (Solaris).  */
	#define SHN_HIPROC      0xff1f          /* End of processor-specific */
	#define SHN_LOOS        0xff20          /* Start of OS-specific */
	#define SHN_HIOS        0xff3f          /* End of OS-specific */
	#define SHN_ABS         0xfff1          /* Associated symbol is absolute */
	#define SHN_COMMON      0xfff2          /* Associated symbol is common */
	#define SHN_XINDEX      0xffff          /* Index is in extra table.  */
	#define SHN_HIRESERVE   0xffff          /* End of reserved indices */

