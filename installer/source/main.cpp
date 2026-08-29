#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// Embedded by bin2o from data/MiniGrok.3gx
extern "C" {
    extern const u8  MiniGrok_3gx[];
    extern const u32 MiniGrok_3gx_size;
}

static void ensureDir(const char *path)
{
    mkdir(path, 0777);
}

static bool writeFile(const char *path, const void *data, u32 size)
{
    FILE *f = fopen(path, "wb");
    if (!f)
        return false;
    size_t w = fwrite(data, 1, size, f);
    fclose(f);
    return w == size;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("MiniGrok Installer\n");
    printf("==================\n\n");

    ensureDir("sdmc:/luma");
    ensureDir("sdmc:/luma/plugins");
    ensureDir("sdmc:/luma/plugins/MiniGrok");

    printf("Installing default.3gx ...\n");
    printf("Size: %u bytes\n\n", (unsigned)MiniGrok_3gx_size);

    bool ok = writeFile("sdmc:/luma/plugins/default.3gx",
                        MiniGrok_3gx, MiniGrok_3gx_size);

    if (ok)
    {
        printf("SUCCESS!\n\n");
        printf("Installed to:\n");
        printf("  sd:/luma/plugins/default.3gx\n\n");
        printf("Next:\n");
        printf(" 1. Rosalina -> Plugin Loader ON\n");
        printf(" 2. Reboot the 3DS\n");
        printf(" 3. Start any game\n");
        printf(" 4. Hold SELECT + press X\n");
    }
    else
    {
        printf("FAILED to write file.\n");
        printf("Check SD card / write protection.\n");
    }

    printf("\nPress START to exit.\n");
    while (aptMainLoop())
    {
        hidScanInput();
        if (hidKeysDown() & KEY_START)
            break;
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
