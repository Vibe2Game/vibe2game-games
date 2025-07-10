Box cubes[26];
int cube_layer[26];
Vector3 original_locs[26];
Vector3 dirs[6];
Vector3 empty_loc;
float spacing;
Material red_mat;
Material orange_mat;
Material cyan_mat;
Text timer_text;
Text best_text;
Text recent_text;
Text reset_text;
float start_time;
float best_time;
float recent_time;
bool solved;
PointLight key_light;
PointLight fill_light;
Text how_text;
bool show_how;

void Game_Update() {
   if (Game_IsInitializing()) {
      spacing = 1.1f;
      dirs[0] = Vector3_Create(spacing, 0.0f, 0.0f);
      dirs[1] = Vector3_Create(-spacing, 0.0f, 0.0f);
      dirs[2] = Vector3_Create(0.0f, spacing, 0.0f);
      dirs[3] = Vector3_Create(0.0f, -spacing, 0.0f);
      dirs[4] = Vector3_Create(0.0f, 0.0f, spacing);
      dirs[5] = Vector3_Create(0.0f, 0.0f, -spacing);
      red_mat = Material_Create();
      Material_SetColor(red_mat, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
      Material_SetGlossiness(red_mat, 0.25f);
      orange_mat = Material_Create();
      Material_SetColor(orange_mat, Color_Create(1.0f, 0.5f, 0.0f, 1.0f));
      Material_SetGlossiness(orange_mat, 0.25f);
      cyan_mat = Material_Create();
      Material_SetColor(cyan_mat, Color_Create(0.0f, 0.8f, 0.8f, 1.0f));
      Material_SetGlossiness(cyan_mat, 0.25f);
      int cube_cnt = 0;
      for (int iz = 0; iz < 3; iz++) {
         for (int iy = 0; iy < 3; iy++) {
            for (int ix = 0; ix < 3; ix++) {
               if (ix == 1 && iy == 1 && iz == 1) continue;
               cubes[cube_cnt] = Primitive_CreateBox();
               Primitive_SetBoxDimensions(cubes[cube_cnt], Vector3_Create(1.0f, 1.0f, 1.0f));
               Primitive_SetBoxCornerRadius(cubes[cube_cnt], 0.1f);
               Vector3 loc = Vector3_Create((float)(ix - 1) * spacing, (float)(iy - 1) * spacing, (float)(iz - 1) * spacing);
               Primitive_SetLocation(cubes[cube_cnt], loc);
               original_locs[cube_cnt] = loc;
               Material mat;
               if (iy == 2) {
                  mat = red_mat;
               } else if (iy == 0) {
                  mat = orange_mat;
               } else {
                  mat = cyan_mat;
               }
               Primitive_SetMaterial(cubes[cube_cnt], mat);
               cube_layer[cube_cnt] = iy;
               cube_cnt++;
            }
         }
      }
      empty_loc = Vector3_Create(0.0f, 0.0f, 0.0f);
      Randomizer_SetDeterministicSeed(42);
      for (int s = 0; s < 200; s++) {
         int num_possible = 0;
         int possible_dirs[6];
         for (int d = 0; d < 6; d++) {
            Vector3 cand = empty_loc + dirs[d];
            int px = (int)Float_Round(cand.x / spacing) + 1;
            int py = (int)Float_Round(cand.y / spacing) + 1;
            int pz = (int)Float_Round(cand.z / spacing) + 1;
            if (px >= 0 && px <= 2 && py >= 0 && py <= 2 && pz >= 0 && pz <= 2) {
               possible_dirs[num_possible] = d;
               num_possible++;
            }
         }
         if (num_possible > 0) {
            int rand_idx = Int_RandomizeDeterministic(0, num_possible - 1);
            int d = possible_dirs[rand_idx];
            Vector3 move_from = empty_loc + dirs[d];
            for (int j = 0; j < 26; j++) {
               if (Vector3_Distance(Primitive_GetLocation(cubes[j]), move_from) < FLT_EPSILON * 100.0f) {
                  Primitive_SetLocation(cubes[j], empty_loc);
                  empty_loc = move_from;
                  break;
               }
            }
         }
      }
      start_time = Game_GetTime();
      solved = false;
      best_time = FLT_MAX;
      recent_time = 0.0f;
      show_how = true;
      timer_text = Primitive_CreateText("Time: (#0.1)");
      Primitive_SetTextFont(timer_text, 0);
      Primitive_SetTextSize(timer_text, 0.4f, 0.1f);
      Primitive_SetLocation(timer_text, Vector3_Create(-0.75f, 0.9f, 0.0f));
      Primitive_SetTextColor(timer_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(timer_text, Color_Create(1.0f, 0.5f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(timer_text, 10);
      Primitive_SetTextBackdropBlur(timer_text, 8);
      best_text = Primitive_CreateText("Best: (#0.1)");
      Primitive_SetTextFont(best_text, 0);
      Primitive_SetTextSize(best_text, 0.4f, 0.1f);
      Primitive_SetLocation(best_text, Vector3_Create(-0.75f, 0.75f, 0.0f));
      Primitive_SetTextColor(best_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(best_text, Color_Create(1.0f, 0.5f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(best_text, 10);
      Primitive_SetTextBackdropBlur(best_text, 8);
      recent_text = Primitive_CreateText("Last: (#0.1)");
      Primitive_SetTextFont(recent_text, 0);
      Primitive_SetTextSize(recent_text, 0.4f, 0.1f);
      Primitive_SetLocation(recent_text, Vector3_Create(-0.75f, 0.6f, 0.0f));
      Primitive_SetTextColor(recent_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(recent_text, Color_Create(1.0f, 0.5f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(recent_text, 10);
      Primitive_SetTextBackdropBlur(recent_text, 8);
      reset_text = Primitive_CreateText("Reset");
      Primitive_SetTextFont(reset_text, 0);
      Primitive_SetTextSize(reset_text, 0.4f, 0.1f);
      Primitive_SetLocation(reset_text, Vector3_Create(0.75f, -0.9f, 0.0f));
      Primitive_SetTextColor(reset_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(reset_text, Color_Create(1.0f, 0.5f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(reset_text, 10);
      Primitive_SetTextBackdropBlur(reset_text, 8);
      how_text = Primitive_CreateText("How to play: Click on a cube adjacent to the empty cell to move it. The goal is to restore the original arrangement where the top 9 cubes are red, the bottom 9 are orange, and the middle layer is cyan.");
      Primitive_SetTextFont(how_text, 0);
      Primitive_SetTextWrapping(how_text, false);
      Primitive_SetTextSize(how_text, 1.333f, 1.333f);
      Primitive_SetTextMargin(how_text, 0.1f, 0.1f);
      Primitive_SetTextColor(how_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(how_text, Color_Create(0.0f, 0.0f, 0.0f, 0.3f));
      Primitive_SetTextCornerRadius(how_text, 10);
      Primitive_SetTextBackdropBlur(how_text, 8);
      Primitive_SetLocation(how_text, Vector3_Create(0.0f, 0.0f, 0.0f));
      AmbientLight_Set(Color_Create(0.1f, 0.1f, 0.1f, 1.0f));
      Environment_SetGradient(Color_Create(0.8f, 0.8f, 0.8f, 1.0f), Color_Create(0.4f, 0.4f, 0.4f, 1.0f), Color_Create(0.2f, 0.2f, 0.2f, 1.0f), Color_Create(0.1f, 0.1f, 0.1f, 1.0f), 0.33f, 0.66f);
      key_light = PointLight_Create(0.0f);
      PointLight_SetLocation(key_light, Vector3_Create(-4.5f, 4.5f, 3.0f));
      PointLight_SetColor(key_light, Color_Create(0.70f, 0.70f, 0.70f, 1.0f));
      PointLight_SetEmissivityRange(key_light, 60.0f);
      fill_light = PointLight_Create(0.0f);
      PointLight_SetLocation(fill_light, Vector3_Create(3.6f, 3.6f, 2.4f));
      PointLight_SetColor(fill_light, Color_Create(0.35f, 0.35f, 0.35f, 1.0f));
      PointLight_SetEmissivityRange(fill_light, 90.0f);
      View_SetMode(2);
      View_InitOrbit(30.0f, 45.0f, 6.0f);
      View_SetLookAtLocation(Vector3_Create(0.0f, 0.0f, 0.0f));
      View_SetResponse(1.0f, 1.0f);
      View_SetFieldOfViewAngle(60.0f);
      View_SetClipPlanes(0.1f, 100.0f);
      View_SetZoomSensitivity(5.0f);
   }
   if (Mouse_Click()) {
      int clicked = Clicked_GetPrimitive();
      if (clicked == how_text) {
         show_how = false;
      } else if (clicked == reset_text) {
         for (int i = 0; i < 26; i++) {
            Primitive_SetLocation(cubes[i], original_locs[i]);
         }
         empty_loc = Vector3_Create(0.0f, 0.0f, 0.0f);
         for (int s = 0; s < 200; s++) {
            int num_possible = 0;
            int possible_dirs[6];
            for (int d = 0; d < 6; d++) {
               Vector3 cand = empty_loc + dirs[d];
               int px = (int)Float_Round(cand.x / spacing) + 1;
               int py = (int)Float_Round(cand.y / spacing) + 1;
               int pz = (int)Float_Round(cand.z / spacing) + 1;
               if (px >= 0 && px <= 2 && py >= 0 && py <= 2 && pz >= 0 && pz <= 2) {
                  possible_dirs[num_possible] = d;
                  num_possible++;
               }
            }
            if (num_possible > 0) {
               int rand_idx = Int_RandomizeDeterministic(0, num_possible - 1);
               int d = possible_dirs[rand_idx];
               Vector3 move_from = empty_loc + dirs[d];
               for (int j = 0; j < 26; j++) {
                  if (Vector3_Distance(Primitive_GetLocation(cubes[j]), move_from) < FLT_EPSILON * 100.0f) {
                     Primitive_SetLocation(cubes[j], empty_loc);
                     empty_loc = move_from;
                     break;
                  }
               }
            }
         }
         start_time = Game_GetTime();
         solved = false;
         show_how = true;
      } else if (Primitive_IsBox(clicked)) {
         for (int i = 0; i < 26; i++) {
            if (cubes[i] == clicked) {
               Vector3 cube_loc = Primitive_GetLocation(cubes[i]);
               Vector3 diff = cube_loc - empty_loc;
               float abs_dx = Float_Abs(diff.x);
               float abs_dy = Float_Abs(diff.y);
               float abs_dz = Float_Abs(diff.z);
               bool adjacent = (abs_dx == spacing && abs_dy == 0.0f && abs_dz == 0.0f) ||
                                (abs_dy == spacing && abs_dx == 0.0f && abs_dz == 0.0f) ||
                                (abs_dz == spacing && abs_dx == 0.0f && abs_dy == 0.0f);
               if (adjacent && !solved) {
                  Primitive_SetLocation(cubes[i], empty_loc);
                  empty_loc = cube_loc;
               }
               break;
            }
         }
      }
   }
   bool is_solved = true;
   for (int i = 0; i < 26; i++) {
      Vector3 loc = Primitive_GetLocation(cubes[i]);
      int py = (int)Float_Round(loc.y / spacing) + 1;
      if (cube_layer[i] != py) {
         is_solved = false;
         break;
      }
   }
   if (is_solved && !solved) {
      float elapsed = Game_GetTime() - start_time;
      recent_time = elapsed;
      if (elapsed < best_time) {
         best_time = elapsed;
      }
   }
   solved = is_solved;
   float timer_value;
   if (solved) {
      timer_value = recent_time;
   } else {
      timer_value = Game_GetTime() - start_time;
   }
   Primitive_SetTextNumber(timer_text, 0, timer_value);
   Primitive_SetTextNumber(recent_text, 0, recent_time);
   float best_value;
   if (best_time == FLT_MAX) {
      best_value = 0.0f;
   } else {
      best_value = best_time;
   }
   Primitive_SetTextNumber(best_text, 0, best_value);
   Primitive_SetInvisible(how_text, !show_how);
}