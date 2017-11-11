ENTRY(_start)
SECTIONS
{
  . = 0x0100000;        /* Cargar el kernel a partir de mega de memoria, 
                           Todas las referncias a datos de haran a partir de esa direccion */
  .text : { 
      *(.text)          /* Juntar el codigo y los datos de readonly en la mimsma seccion */
      *(.rodata)
      . = ALIGN(4096);  /* Alineacion de 4KB para el paginado */
  }

  .data : { 
      *(.data)
      . = ALIGN(4096);
  }

  .bss : {
      *(.bss)
      . = ALIGN(4096);
  }

  /DISCARD/ : {         /* Descartar estas dos secciones del .elf final */
      *(.eh_frame)  
      *(.comment)
  }

  end__ = .;

}
