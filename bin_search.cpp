#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
  if (argc != 4) {
    std::cout << "usage:\n"
              << "  bin_search  3gx-file  begin-val  end-val\n";

    return -1;
  }

  FILE *fp = fopen(argv[1], "r");

  if (!fp) {
    std::cout << "cannot open.\n";
    return -1;
  }

  uint32_t begin = std::stoul(argv[2], nullptr, 16);
  uint32_t end = std::stoul(argv[3], nullptr, 16);

  fseek(fp, 0, SEEK_END);

  size_t filesize = ftell(fp);
  auto buf = new uint8_t[filesize];

  fseek(fp, 0, SEEK_SET);

  fread(buf, filesize, 1, fp);

  for (auto ptr = (uint32_t *)buf;
       (size_t)ptr < (size_t)(buf + filesize); ptr++) {
    if (begin < *ptr && *ptr < end) {
      printf("%zx: %08X\n", (size_t)(ptr) - (size_t)buf, *ptr);
    }
  }

  fclose(fp);
}