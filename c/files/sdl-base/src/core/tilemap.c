int unit_width = 16;
int unit_height = 16;

int level_width = 64;
int level_height = 16;
int level[level_width * level_height];

// drawing map we add camera offset
// drawing objects we subtract to bring them back into viewable space

// may have to check if_focused() when handling input
int main(void)
{
  for (int x = 0; x < level_width; ++x) {
    for (int y = 0; y < level_height; ++y) {
      switch (level[y * level_width + x]) {
      case BLOCK:
        // ...
      }
    }
  }

}
