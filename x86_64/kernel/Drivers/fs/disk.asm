global ata_read_sectors_via_lba
ata_read_sectors_via_lba:

    mov eax, 15

    ret

err:

    int 8
