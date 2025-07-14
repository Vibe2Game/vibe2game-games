Sphere racers[15];
Material mats[15];
float offset_x[15];
float speeds[15];
float progress[15];
Spline path;
Text start_btn;
Text reset_btn;
bool racing;
float path_length;
Triangle path_triangles[15][100];
Material gate_mat;
Text place_labels[3];
Color racer_colors[15];
bool finished[15];
int finish_index;
float elapsed_time;
Triangle gate_tris[12];
Triangle finish_text_tris[32];
int letter_tri_starts[6];
int letter_tri_counts[6];
Vector3 start_look_at;
Vector3 end_look_at;
bool transitioning;
float transition_start_time;
Material path_mats[15];
bool race_ended;
int selected_racer;
Text bet_types[3];
float balance;
Text balance_text;
float bet_amount;
Text bet_amount_text;
Text plus_btn;
Text minus_btn;
int current_bet_type;
int finish_order[15];
float transition_duration;
Text win_label;
Text lose_label;
void Game_Update() {
   if (Game_IsInitializing()) {
      racing = false;
      start_btn = Primitive_CreateText("Start");
      Primitive_SetTextFont(start_btn, 0);
      Primitive_SetTextWrapping(start_btn, false);
      Primitive_SetTextSize(start_btn, 0.3f, 0.08f);
      Primitive_SetTextMargin(start_btn, 0.01f, 0.01f);
      Primitive_SetTextColor(start_btn, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(start_btn, Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(start_btn, 10);
      Primitive_SetTextBackdropBlur(start_btn, 0);
      Primitive_SetLocation(start_btn, Vector3_Create(-0.3f, -0.9f, 0.0f));
      reset_btn = Primitive_CreateText("Reset");
      Primitive_SetTextFont(reset_btn, 0);
      Primitive_SetTextWrapping(reset_btn, false);
      Primitive_SetTextSize(reset_btn, 0.3f, 0.08f);
      Primitive_SetTextMargin(reset_btn, 0.01f, 0.01f);
      Primitive_SetTextColor(reset_btn, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(reset_btn, Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(reset_btn, 10);
      Primitive_SetTextBackdropBlur(reset_btn, 0);
      Primitive_SetLocation(reset_btn, Vector3_Create(0.3f, -0.9f, 0.0f));
      int i;
      for (i = 0; i < 3; i = (i + 1)) {
         if (i == 0) {
            place_labels[i] = Primitive_CreateText("1st");
         }
         if (i == 1) {
            place_labels[i] = Primitive_CreateText("2nd");
         }
         if (i == 2) {
            place_labels[i] = Primitive_CreateText("3rd");
         }
         Primitive_SetTextFont(place_labels[i], 0);
         Primitive_SetTextWrapping(place_labels[i], false);
         Primitive_SetTextSize(place_labels[i], 0.4f, 0.12f);
         Primitive_SetTextMargin(place_labels[i], 0.01f, 0.01f);
         Primitive_SetTextColor(place_labels[i], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
         Primitive_SetTextBackgroundColor(place_labels[i], Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
         Primitive_SetTextCornerRadius(place_labels[i], 10);
         Primitive_SetTextBackdropBlur(place_labels[i], 0);
         Primitive_SetLocation(place_labels[i], Vector3_Create(0.75f, (0.85f - ((float)i * 0.15f)), 0.0f));
         Primitive_SetInvisible(place_labels[i], true);
      }
      path = Spline_Create(8);
      int j;
      for (i = 0; i < 15; i = (i + 1)) {
         float hue = (((float)i / 14.0f) * 360.0f);
         Color col = HSVToRGB(hue, 1.0f, 1.0f);
         racer_colors[i] = col;
         mats[i] = Material_Create();
         Material_SetColor(mats[i], racer_colors[i]);
         Material_SetGlossiness(mats[i], 0.5f);
         path_mats[i] = Material_Create();
         Material_SetColor(path_mats[i], racer_colors[i]);
         Material_SetGlossiness(path_mats[i], 0.05f);
         racers[i] = Primitive_CreateSphere();
         Primitive_SetSphereRadius(racers[i], 1.0f);
         Primitive_SetMaterial(racers[i], mats[i]);
         offset_x[i] = ((float)(i - 7) * 3.0f);
         speeds[i] = Float_Randomize(9.8f, 10.2f);
         progress[i] = 0.0f;
         finished[i] = false;
      }
      for (i = 0; i < 15; i = (i + 1)) {
         for (j = 0; j < 100; j = (j + 1)) {
            path_triangles[i][j] = Primitive_CreateTriangle();
            float s = 1.5f;
            float h = (Float_Sqrt(3.0f) * s) / 2.0f;
            Vector3 v0 = Vector3_Create((-s / 2.0f), 0.0f, 0.0f);
            Vector3 v1 = Vector3_Create((s / 2.0f), 0.0f, 0.0f);
            Vector3 v2 = Vector3_Create(0.0f, 0.0f, -h);
            Primitive_SetTriangleVertices(path_triangles[i][j], v0, v1, v2);
            Primitive_SetMaterial(path_triangles[i][j], path_mats[i]);
         }
      }
      gate_mat = Material_Create();
      Material_SetColor(gate_mat, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Material_SetGlossiness(gate_mat, 0.05f);
      Vector3 post_v0 = Vector3_Create(-1.0f, -5.0f, 0.0f);
      Vector3 post_v1 = Vector3_Create(1.0f, -5.0f, 0.0f);
      Vector3 post_v2 = Vector3_Create(-1.0f, 5.0f, 0.0f);
      Vector3 post_v3 = Vector3_Create(1.0f, 5.0f, 0.0f);
      Vector3 bar_v0 = Vector3_Create(-26.0f, -1.0f, 0.0f);
      Vector3 bar_v1 = Vector3_Create(26.0f, -1.0f, 0.0f);
      Vector3 bar_v2 = Vector3_Create(-26.0f, 1.0f, 0.0f);
      Vector3 bar_v3 = Vector3_Create(26.0f, 1.0f, 0.0f);
      for (i = 0; i < 12; i = (i + 1)) {
         gate_tris[i] = Primitive_CreateTriangle();
         Primitive_SetMaterial(gate_tris[i], gate_mat);
      }
      Primitive_SetTriangleVertices(gate_tris[0], post_v0, post_v1, post_v2);
      Primitive_SetTriangleVertices(gate_tris[1], post_v1, post_v3, post_v2);
      Primitive_SetTriangleVertices(gate_tris[2], post_v0, post_v1, post_v2);
      Primitive_SetTriangleVertices(gate_tris[3], post_v1, post_v3, post_v2);
      Primitive_SetTriangleVertices(gate_tris[4], bar_v0, bar_v1, bar_v2);
      Primitive_SetTriangleVertices(gate_tris[5], bar_v1, bar_v3, bar_v2);
      Primitive_SetTriangleVertices(gate_tris[6], post_v0, post_v1, post_v2);
      Primitive_SetTriangleVertices(gate_tris[7], post_v1, post_v3, post_v2);
      Primitive_SetTriangleVertices(gate_tris[8], post_v0, post_v1, post_v2);
      Primitive_SetTriangleVertices(gate_tris[9], post_v1, post_v3, post_v2);
      Primitive_SetTriangleVertices(gate_tris[10], bar_v0, bar_v1, bar_v2);
      Primitive_SetTriangleVertices(gate_tris[11], bar_v1, bar_v3, bar_v2);
      for (i = 0; i < 32; i = (i + 1)) {
         finish_text_tris[i] = Primitive_CreateTriangle();
         Primitive_SetMaterial(finish_text_tris[i], gate_mat);
      }
      Vector3 f_v0 = Vector3_Create(-2.0f, -5.0f, 0.0f);
      Vector3 f_v1 = Vector3_Create(-1.0f, -5.0f, 0.0f);
      Vector3 f_v2 = Vector3_Create(-2.0f, 5.0f, 0.0f);
      Vector3 f_v3 = Vector3_Create(-1.0f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[0], f_v0, f_v1, f_v2);
      Primitive_SetTriangleVertices(finish_text_tris[1], f_v1, f_v3, f_v2);
      Vector3 f_v4 = Vector3_Create(-2.0f, 4.0f, 0.0f);
      Vector3 f_v5 = Vector3_Create(2.0f, 4.0f, 0.0f);
      Vector3 f_v6 = Vector3_Create(-2.0f, 5.0f, 0.0f);
      Vector3 f_v7 = Vector3_Create(2.0f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[2], f_v4, f_v5, f_v6);
      Primitive_SetTriangleVertices(finish_text_tris[3], f_v5, f_v7, f_v6);
      Vector3 f_v8 = Vector3_Create(-2.0f, -1.0f, 0.0f);
      Vector3 f_v9 = Vector3_Create(1.0f, -1.0f, 0.0f);
      Vector3 f_v10 = Vector3_Create(-2.0f, 0.0f, 0.0f);
      Vector3 f_v11 = Vector3_Create(1.0f, 0.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[4], f_v8, f_v9, f_v10);
      Primitive_SetTriangleVertices(finish_text_tris[5], f_v9, f_v11, f_v10);
      Vector3 i1_v0 = Vector3_Create(-0.5f, -5.0f, 0.0f);
      Vector3 i1_v1 = Vector3_Create(0.5f, -5.0f, 0.0f);
      Vector3 i1_v2 = Vector3_Create(-0.5f, 5.0f, 0.0f);
      Vector3 i1_v3 = Vector3_Create(0.5f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[6], i1_v0, i1_v1, i1_v2);
      Primitive_SetTriangleVertices(finish_text_tris[7], i1_v1, i1_v3, i1_v2);
      Vector3 n_v0 = Vector3_Create(-2.0f, -5.0f, 0.0f);
      Vector3 n_v1 = Vector3_Create(-1.0f, -5.0f, 0.0f);
      Vector3 n_v2 = Vector3_Create(-2.0f, 5.0f, 0.0f);
      Vector3 n_v3 = Vector3_Create(-1.0f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[8], n_v0, n_v1, n_v2);
      Primitive_SetTriangleVertices(finish_text_tris[9], n_v1, n_v3, n_v2);
      Vector3 n_v4 = Vector3_Create(1.0f, -5.0f, 0.0f);
      Vector3 n_v5 = Vector3_Create(2.0f, -5.0f, 0.0f);
      Vector3 n_v6 = Vector3_Create(1.0f, 5.0f, 0.0f);
      Vector3 n_v7 = Vector3_Create(2.0f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[10], n_v4, n_v5, n_v6);
      Primitive_SetTriangleVertices(finish_text_tris[11], n_v5, n_v7, n_v6);
      Vector3 n_start = Vector3_Create(-1.0f,5.0f,0.0f);
      Vector3 n_end = Vector3_Create(1.0f,-5.0f,0.0f);
      Vector3 d = n_end - n_start;
      Vector3 perp = Vector3_Create(-d.y, d.x, 0.0f);
      float perp_length = Vector3_Length(perp);
      float thick_half = 0.5f;
      Vector3 norm_perp = perp * (1.0f / perp_length);
      Vector3 offset = norm_perp * thick_half;
      Vector3 c1 = n_start + offset;
      Vector3 c2 = n_start - offset;
      Vector3 c3 = n_end + offset;
      Vector3 c4 = n_end - offset;
      Primitive_SetTriangleVertices(finish_text_tris[12], c1, c2, c3);
      Primitive_SetTriangleVertices(finish_text_tris[13], c2, c4, c3);
      Vector3 i2_v0 = Vector3_Create(-0.5f, -5.0f, 0.0f);
      Vector3 i2_v1 = Vector3_Create(0.5f, -5.0f, 0.0f);
      Vector3 i2_v2 = Vector3_Create(-0.5f, 5.0f, 0.0f);
      Vector3 i2_v3 = Vector3_Create(0.5f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[14], i2_v0, i2_v1, i2_v2);
      Primitive_SetTriangleVertices(finish_text_tris[15], i2_v1, i2_v3, i2_v2);
      Vector3 s_v0 = Vector3_Create(-2.0f,4.0f,0.0f);
      Vector3 s_v1 = Vector3_Create(2.0f,4.0f,0.0f);
      Vector3 s_v2 = Vector3_Create(-2.0f,5.0f,0.0f);
      Vector3 s_v3 = Vector3_Create(2.0f,5.0f,0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[16], s_v0, s_v1, s_v2);
      Primitive_SetTriangleVertices(finish_text_tris[17], s_v1, s_v3, s_v2);
      Vector3 s_v4 = Vector3_Create(-2.0f,-5.0f,0.0f);
      Vector3 s_v5 = Vector3_Create(2.0f,-5.0f,0.0f);
      Vector3 s_v6 = Vector3_Create(-2.0f,-4.0f,0.0f);
      Vector3 s_v7 = Vector3_Create(2.0f,-4.0f,0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[18], s_v4, s_v5, s_v6);
      Primitive_SetTriangleVertices(finish_text_tris[19], s_v5, s_v7, s_v6);
      Vector3 s_v8 = Vector3_Create(-2.0f,-1.0f,0.0f);
      Vector3 s_v9 = Vector3_Create(2.0f,-1.0f,0.0f);
      Vector3 s_v10 = Vector3_Create(-2.0f,0.0f,0.0f);
      Vector3 s_v11 = Vector3_Create(2.0f,0.0f,0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[20], s_v8, s_v9, s_v10);
      Primitive_SetTriangleVertices(finish_text_tris[21], s_v9, s_v11, s_v10);
      Vector3 s_v12 = Vector3_Create(-2.0f,0.0f,0.0f);
      Vector3 s_v13 = Vector3_Create(-1.0f,0.0f,0.0f);
      Vector3 s_v14 = Vector3_Create(-2.0f,5.0f,0.0f);
      Vector3 s_v15 = Vector3_Create(-1.0f,5.0f,0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[22], s_v12, s_v13, s_v14);
      Primitive_SetTriangleVertices(finish_text_tris[23], s_v13, s_v15, s_v14);
      Vector3 s_v16 = Vector3_Create(1.0f,-5.0f,0.0f);
      Vector3 s_v17 = Vector3_Create(2.0f,-5.0f,0.0f);
      Vector3 s_v18 = Vector3_Create(1.0f,0.0f,0.0f);
      Vector3 s_v19 = Vector3_Create(2.0f,0.0f,0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[24], s_v16, s_v17, s_v18);
      Primitive_SetTriangleVertices(finish_text_tris[25], s_v17, s_v19, s_v18);
      Vector3 h_v0 = Vector3_Create(-2.0f, -5.0f, 0.0f);
      Vector3 h_v1 = Vector3_Create(-1.0f, -5.0f, 0.0f);
      Vector3 h_v2 = Vector3_Create(-2.0f, 5.0f, 0.0f);
      Vector3 h_v3 = Vector3_Create(-1.0f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[26], h_v0, h_v1, h_v2);
      Primitive_SetTriangleVertices(finish_text_tris[27], h_v1, h_v3, h_v2);
      Vector3 h_v4 = Vector3_Create(1.0f, -5.0f, 0.0f);
      Vector3 h_v5 = Vector3_Create(2.0f, -5.0f, 0.0f);
      Vector3 h_v6 = Vector3_Create(1.0f, 5.0f, 0.0f);
      Vector3 h_v7 = Vector3_Create(2.0f, 5.0f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[28], h_v4, h_v5, h_v6);
      Primitive_SetTriangleVertices(finish_text_tris[29], h_v5, h_v7, h_v6);
      Vector3 h_v8 = Vector3_Create(-2.0f, -0.5f, 0.0f);
      Vector3 h_v9 = Vector3_Create(2.0f, -0.5f, 0.0f);
      Vector3 h_v10 = Vector3_Create(-2.0f, 0.5f, 0.0f);
      Vector3 h_v11 = Vector3_Create(2.0f, 0.5f, 0.0f);
      Primitive_SetTriangleVertices(finish_text_tris[30], h_v8, h_v9, h_v10);
      Primitive_SetTriangleVertices(finish_text_tris[31], h_v9, h_v11, h_v10);
      letter_tri_starts[0] = 0;
      letter_tri_counts[0] = 6;
      letter_tri_starts[1] = 6;
      letter_tri_counts[1] = 2;
      letter_tri_starts[2] = 8;
      letter_tri_counts[2] = 6;
      letter_tri_starts[3] = 14;
      letter_tri_counts[3] = 2;
      letter_tri_starts[4] = 16;
      letter_tri_counts[4] = 10;
      letter_tri_starts[5] = 26;
      letter_tri_counts[5] = 6;
      ResetPath();
      for (i = 0; i < 15; i = (i + 1)) {
         Vector3 init_pos = Vector3_Create(0.0f, 50.0f, -200.0f) + Vector3_Create(offset_x[i], 0.0f, 0.0f);
         Primitive_SetLocation(racers[i], init_pos);
      }
      View_SetMode(2);
      View_InitOrbit(30.0f, 0.0f, 200.0f);
      View_SetLookAtLocation(start_look_at);
      View_SetZoomSensitivity(5.0f);
      View_SetClipPlanes(0.1f, 1000.0f);
      View_SetFieldOfViewAngle(60.0f);
      AmbientLight_Set(Color_Create(0.0125f, 0.0125f, 0.0125f, 1.0f));
      Environment_SetGradient(Color_Create(0.1f, 0.025f, 0.0f, 1.0f), Color_Create(0.05f, 0.0125f, 0.0f, 1.0f), Color_Create(0.025f, 0.00625f, 0.0f, 1.0f), Color_Create(0.0125f, 0.003125f, 0.0f, 1.0f), 0.33f, 0.66f);
      PointLight keyLight = PointLight_Create(0.0f);
      PointLight_SetLocation(keyLight, Vector3_Create(-1.5f, 1.5f, 1.0f));
      PointLight_SetColor(keyLight, Color_Create(0.70f, 0.70f, 0.70f, 1.0f));
      PointLight_SetEmissivityRange(keyLight, 200.0f);
      PointLight fillLight = PointLight_Create(0.0f);
      PointLight_SetLocation(fillLight, Vector3_Create(1.2f, 1.2f, 0.8f));
      PointLight_SetColor(fillLight, Color_Create(0.35f, 0.35f, 0.35f, 1.0f));
      PointLight_SetEmissivityRange(fillLight, 300.0f);
      PointLight startLight = PointLight_Create(0.0f);
      PointLight_SetLocation(startLight, Vector3_Create(0.0f, 60.0f, -200.0f));
      PointLight_SetColor(startLight, Color_Create(0.5f, 0.5f, 0.5f, 1.0f));
      PointLight_SetEmissivityRange(startLight, 100.0f);
      elapsed_time = 0.0f;
      finish_index = 0;
      for (i = 0; i < 15; i = (i + 1)) {
         finished[i] = false;
      }
      transitioning = false;
      race_ended = false;
      selected_racer = -1;
      bet_types[0] = Primitive_CreateText("Win");
      Primitive_SetTextFont(bet_types[0], 0);
      Primitive_SetTextWrapping(bet_types[0], false);
      Primitive_SetTextSize(bet_types[0], 0.3f, 0.08f);
      Primitive_SetTextMargin(bet_types[0], 0.01f, 0.01f);
      Primitive_SetTextColor(bet_types[0], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(bet_types[0], Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(bet_types[0], 10);
      Primitive_SetTextBackdropBlur(bet_types[0], 0);
      Primitive_SetLocation(bet_types[0], Vector3_Create(-0.6f, -0.75f, 0.0f));
      bet_types[1] = Primitive_CreateText("Place");
      Primitive_SetTextFont(bet_types[1], 0);
      Primitive_SetTextWrapping(bet_types[1], false);
      Primitive_SetTextSize(bet_types[1], 0.3f, 0.08f);
      Primitive_SetTextMargin(bet_types[1], 0.01f, 0.01f);
      Primitive_SetTextColor(bet_types[1], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(bet_types[1], Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(bet_types[1], 10);
      Primitive_SetTextBackdropBlur(bet_types[1], 0);
      Primitive_SetLocation(bet_types[1], Vector3_Create(-0.6f, -0.75f, 0.0f));
      Primitive_SetInvisible(bet_types[1], true);
      bet_types[2] = Primitive_CreateText("Show");
      Primitive_SetTextFont(bet_types[2], 0);
      Primitive_SetTextWrapping(bet_types[2], false);
      Primitive_SetTextSize(bet_types[2], 0.3f, 0.08f);
      Primitive_SetTextMargin(bet_types[2], 0.01f, 0.01f);
      Primitive_SetTextColor(bet_types[2], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(bet_types[2], Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(bet_types[2], 10);
      Primitive_SetTextBackdropBlur(bet_types[2], 0);
      Primitive_SetLocation(bet_types[2], Vector3_Create(-0.6f, -0.75f, 0.0f));
      Primitive_SetInvisible(bet_types[2], true);
      current_bet_type = 0;
      balance = 100.0f;
      balance_text = Primitive_CreateText("Balance: $(#0.0)");
      Primitive_SetTextFont(balance_text, 0);
      Primitive_SetTextWrapping(balance_text, false);
      Primitive_SetTextSize(balance_text, 0.4f, 0.08f);
      Primitive_SetTextMargin(balance_text, 0.01f, 0.01f);
      Primitive_SetTextColor(balance_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(balance_text, Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(balance_text, 10);
      Primitive_SetTextBackdropBlur(balance_text, 0);
      Primitive_SetLocation(balance_text, Vector3_Create(0.6f, -0.75f, 0.0f));
      Primitive_SetTextNumber(balance_text, 0, balance);
      bet_amount = 10.0f;
      bet_amount_text = Primitive_CreateText("Bet: $(#0.0)");
      Primitive_SetTextFont(bet_amount_text, 0);
      Primitive_SetTextWrapping(bet_amount_text, false);
      Primitive_SetTextSize(bet_amount_text, 0.4f, 0.08f);
      Primitive_SetTextMargin(bet_amount_text, 0.01f, 0.01f);
      Primitive_SetTextColor(bet_amount_text, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(bet_amount_text, Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(bet_amount_text, 10);
      Primitive_SetTextBackdropBlur(bet_amount_text, 0);
      Primitive_SetLocation(bet_amount_text, Vector3_Create(0.0f, -0.75f, 0.0f));
      Primitive_SetTextNumber(bet_amount_text, 0, bet_amount);
      plus_btn = Primitive_CreateText("+");
      Primitive_SetTextFont(plus_btn, 0);
      Primitive_SetTextWrapping(plus_btn, false);
      Primitive_SetTextSize(plus_btn, 0.15f, 0.08f);
      Primitive_SetTextMargin(plus_btn, 0.01f, 0.01f);
      Primitive_SetTextColor(plus_btn, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(plus_btn, Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(plus_btn, 10);
      Primitive_SetTextBackdropBlur(plus_btn, 0);
      Primitive_SetLocation(plus_btn, Vector3_Create(0.3f, -0.75f, 0.0f));
      minus_btn = Primitive_CreateText("-");
      Primitive_SetTextFont(minus_btn, 0);
      Primitive_SetTextWrapping(minus_btn, false);
      Primitive_SetTextSize(minus_btn, 0.15f, 0.08f);
      Primitive_SetTextMargin(minus_btn, 0.01f, 0.01f);
      Primitive_SetTextColor(minus_btn, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(minus_btn, Color_Create(0.2f, 0.2f, 0.2f, 0.8f));
      Primitive_SetTextCornerRadius(minus_btn, 10);
      Primitive_SetTextBackdropBlur(minus_btn, 0);
      Primitive_SetLocation(minus_btn, Vector3_Create(-0.3f, -0.75f, 0.0f));
      win_label = Primitive_CreateText("You win $(#0.0)");
      Primitive_SetTextFont(win_label, 0);
      Primitive_SetTextWrapping(win_label, false);
      Primitive_SetTextSize(win_label, 1.0f, 0.3f);
      Primitive_SetTextMargin(win_label, 0.01f, 0.01f);
      Primitive_SetTextColor(win_label, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(win_label, Color_Create(0.2f, 0.2f, 0.2f, 0.2f));
      Primitive_SetTextCornerRadius(win_label, 10);
      Primitive_SetTextBackdropBlur(win_label, 8);
      Primitive_SetLocation(win_label, Vector3_Create(0.0f, 0.0f, 0.0f));
      Primitive_SetInvisible(win_label, true);
      lose_label = Primitive_CreateText("You lose $(#0.0)");
      Primitive_SetTextFont(lose_label, 0);
      Primitive_SetTextWrapping(lose_label, false);
      Primitive_SetTextSize(lose_label, 1.0f, 0.3f);
      Primitive_SetTextMargin(lose_label, 0.01f, 0.01f);
      Primitive_SetTextColor(lose_label, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(lose_label, Color_Create(0.2f, 0.2f, 0.2f, 0.2f));
      Primitive_SetTextCornerRadius(lose_label, 10);
      Primitive_SetTextBackdropBlur(lose_label, 8);
      Primitive_SetLocation(lose_label, Vector3_Create(0.0f, 0.0f, 0.0f));
      Primitive_SetInvisible(lose_label, true);
   }
   float deltaTime = Game_GetTick();
   int clicked = Clicked_GetPrimitive();
   if (Primitive_IsText(clicked)) {
      if (clicked == start_btn) {
         if (racing == false) {
            racing = true;
            Primitive_SetInvisible(start_btn, true);
            elapsed_time = 0.0f;
            finish_index = 0;
            int l;
            for (l = 0; l < 15; l = (l + 1)) {
               finished[l] = false;
            }
            for (l = 0; l < 3; l = (l + 1)) {
               Primitive_SetInvisible(place_labels[l], true);
            }
            transitioning = true;
            transition_start_time = Game_GetTime();
         }
      }
      if (clicked == reset_btn) {
         racing = false;
         int j;
         Vector3 start = Vector3_Create(0.0f, 50.0f, -200.0f);
         for (j = 0; j < 15; j = (j + 1)) {
            progress[j] = 0.0f;
            Vector3 pos = start + Vector3_Create(offset_x[j], 0.0f, 0.0f);
            Primitive_SetLocation(racers[j], pos);
         }
         Primitive_SetInvisible(start_btn, false);
         ResetPath();
         elapsed_time = 0.0f;
         finish_index = 0;
         int l;
         for (l = 0; l < 15; l = (l + 1)) {
            finished[l] = false;
         }
         for (l = 0; l < 3; l = (l + 1)) {
            Primitive_SetInvisible(place_labels[l], true);
         }
         transitioning = false;
         race_ended = false;
         View_SetLookAtLocation(start_look_at);
         Primitive_SetInvisible(win_label, true);
         Primitive_SetInvisible(lose_label, true);
      }
      if (clicked == bet_types[current_bet_type]) {
         if (racing == false) {
            Primitive_SetInvisible(bet_types[current_bet_type], true);
            current_bet_type = Int_Wrap((current_bet_type + 1), 0, 2);
            Primitive_SetInvisible(bet_types[current_bet_type], false);
            if (selected_racer != -1) {
               Primitive_SetTextBackgroundColor(bet_types[current_bet_type], racer_colors[selected_racer]);
            }
         }
      }
      if (clicked == plus_btn) {
         if (racing == false) {
            bet_amount = (bet_amount + 10.0f);
            bet_amount = Float_Clamp(bet_amount, 0.0f, balance);
            Primitive_SetTextNumber(bet_amount_text, 0, bet_amount);
         }
      }
      if (clicked == minus_btn) {
         if (racing == false) {
            bet_amount = (bet_amount - 10.0f);
            bet_amount = Float_Clamp(bet_amount, 0.0f, balance);
            Primitive_SetTextNumber(bet_amount_text, 0, bet_amount);
         }
      }
   } else {
      if (racing == false) {
         if (Primitive_IsSphere(clicked)) {
            int k;
            for (k = 0; k < 15; k = (k + 1)) {
               if (clicked == racers[k]) {
                  selected_racer = k;
                  Primitive_SetTextBackgroundColor(bet_types[current_bet_type], racer_colors[selected_racer]);
               }
            }
         }
      }
   }
   if (racing) {
      elapsed_time = (elapsed_time + deltaTime);
      bool all_finished = true;
      int k;
      for (k = 0; k < 15; k = (k + 1)) {
         if (progress[k] < 1.0f) {
            float rand = Float_Randomize(0.0f, 1.0f);
            if (rand < 0.01f) {
               speeds[k] = (speeds[k] + Float_Randomize(-0.5f, 0.5f));
               speeds[k] = Float_Clamp(speeds[k], 6.0f, 14.0f);
            }
         }
         progress[k] = (progress[k] + ((speeds[k] / path_length) * deltaTime));
         if (progress[k] > 1.0f) {
            progress[k] = 1.0f;
         }
         Vector3 path_pos = Spline_GetLocationAtTime(path, progress[k]);
         Vector3 racer_pos = path_pos + Vector3_Create(offset_x[k], 0.0f, 0.0f);
         Primitive_SetLocation(racers[k], racer_pos);
         if (progress[k] >= 1.0f) {
            if (finished[k] == false) {
               finished[k] = true;
               finish_order[finish_index] = k;
               if (finish_index < 3) {
                  Primitive_SetTextBackgroundColor(place_labels[finish_index], racer_colors[k]);
                  Primitive_SetInvisible(place_labels[finish_index], false);
               }
               finish_index = (finish_index + 1);
            }
         }
         if (progress[k] < 1.0f) {
            all_finished = false;
         }
      }
      if (all_finished) {
         racing = false;
         race_ended = true;
         if (selected_racer != -1) {
            int place = -1;
            int p;
            for (p = 0; p < 15; p = (p + 1)) {
               if (finish_order[p] == selected_racer) {
                  place = (p + 1);
               }
            }
            bool success = false;
            if (current_bet_type == 0) {
               if (place == 1) {
                  success = true;
               }
            }
            if (current_bet_type == 1) {
               if (place <= 2) {
                  success = true;
               }
            }
            if (current_bet_type == 2) {
               if (place <= 3) {
                  success = true;
               }
            }
            balance = (balance - bet_amount);
            if (success) {
               float multiplier = 0.0f;
               if (current_bet_type == 0) {
                  multiplier = 3.0f;
               }
               if (current_bet_type == 1) {
                  multiplier = 2.0f;
               }
               if (current_bet_type == 2) {
                  multiplier = 1.5f;
               }
               balance = (balance + (multiplier * bet_amount));
               Primitive_SetTextNumber(win_label, 0, (multiplier * bet_amount));
               Primitive_SetInvisible(win_label, false);
            } else {
               Primitive_SetTextNumber(lose_label, 0, bet_amount);
               Primitive_SetInvisible(lose_label, false);
            }
            Primitive_SetTextNumber(balance_text, 0, balance);
            if (bet_amount > balance) {
               bet_amount = balance;
               Primitive_SetTextNumber(bet_amount_text, 0, bet_amount);
            }
         }
      }
   }
   Vector3 current_look_at;
   if (racing || race_ended) {
      if (transitioning) {
         float factor = (Game_GetTime() - transition_start_time) / transition_duration;
         if (factor > 1.0f) {
            transitioning = false;
            current_look_at = end_look_at;
         } else {
            float sin_factor = (0.5f - (0.5f * Float_Cos((PI * factor))));
            current_look_at = Vector3_Interpolate(start_look_at, end_look_at, sin_factor);
         }
      } else {
         current_look_at = end_look_at;
      }
   } else {
      current_look_at = start_look_at;
   }
   View_SetLookAtLocation(current_look_at);
}
Color HSVToRGB(float h, float s, float v) {
   float hh = Float_Wrap(h, 0.0f, 360.0f);
   float c = (v * s);
   float x = (c * (1.0f - Float_Abs((Float_Mod((hh / 60.0f), 2.0f) - 1.0f))));
   float m = (v - c);
   float r = 0.0f;
   float g = 0.0f;
   float b = 0.0f;
   if (hh >= 0.0f) {
      if (hh < 60.0f) {
         r = c;
         g = x;
         b = 0.0f;
      }
   }
   if (hh >= 60.0f) {
      if (hh < 120.0f) {
         r = x;
         g = c;
         b = 0.0f;
      }
   }
   if (hh >= 120.0f) {
      if (hh < 180.0f) {
         r = 0.0f;
         g = c;
         b = x;
      }
   }
   if (hh >= 180.0f) {
      if (hh < 240.0f) {
         r = 0.0f;
         g = x;
         b = c;
      }
   }
   if (hh >= 240.0f) {
      if (hh < 300.0f) {
         r = x;
         g = 0.0f;
         b = c;
      }
   }
   if (hh >= 300.0f) {
      if (hh < 360.0f) {
         r = c;
         g = 0.0f;
         b = x;
      }
   }
   r = (r + m);
   g = (g + m);
   b = (b + m);
   return Color_Create(r, g, b, 1.0f);
}
void ResetPath() {
   Vector3 start = Vector3_Create(0.0f, 50.0f, -200.0f);
   Vector3 end = Vector3_Create(0.0f, 0.0f, 0.0f);
   Vector3 perp1 = Vector3_Create(0.0f, Float_Sqrt(0.5f), Float_Sqrt(0.5f));
   float amp = 30.0f;
   Spline_SetControlPointLocation(path, 0, start);
   Spline_SetControlPointLocation(path, 7, end);
   int i;
   for (i = 1; i < 7; i = (i + 1)) {
      float t = ((float)i / 7.0f);
      Vector3 base = Vector3_Interpolate(start, end, t);
      Vector3 offset = Vector3_Create(0.0f, 0.0f, 0.0f);
      if ((i == 1) || (i == 6)) {
         offset = Vector3_Create(0.0f, 0.0f, 0.0f);
      } else {
         float rand1 = Float_Randomize(-1.0f, 1.0f);
         float factor = Float_Sin((PI * t));
         offset = perp1 * (rand1 * (amp * factor));
      }
      Vector3 pos = base + offset;
      if (i == 1) {
         pos.y = start.y;
      }
      if (i == 6) {
         pos.y = end.y;
      }
      Spline_SetControlPointLocation(path, i, pos);
   }
   path_length = Spline_GetLength(path);
   start_look_at = Spline_GetLocationAtTime(path, 0.05f);
   end_look_at = Spline_GetLocationAtTime(path, 0.95f);
   transition_duration = (path_length / 10.0f) - 1.0f;
   int j;
   for (i = 0; i < 15; i = (i + 1)) {
      for (j = 0; j < 100; j = (j + 1)) {
         float t = ((float)j / 99.0f);
         Vector3 pos = Spline_GetLocationAtTime(path, t);
         pos = pos + Vector3_Create(offset_x[i], 0.0f, 0.0f);
         Primitive_SetLocation(path_triangles[i][j], pos);
         Quaternion ori = Spline_GetOrientationAtTime(path, t, 0.0f, 0.25f);
         Primitive_SetOrientation(path_triangles[i][j], ori);
      }
   }
   Vector3 start_p = Spline_GetLocationAtTime(path, 0.0f);
   Quaternion start_o = Spline_GetOrientationAtTime(path, 0.0f, 0.0f, 0.25f);
   float gate_width = 50.0f;
   float post_height = 10.0f;
   float bar_height = 2.0f;
   Vector3 local_l = Vector3_Create((-gate_width / 2.0f), 0.0f, 0.0f);
   Vector3 world_l = start_p + Vector3_RotateWithQuaternion(local_l, start_o);
   Primitive_SetLocation(gate_tris[0], world_l);
   Primitive_SetOrientation(gate_tris[0], start_o);
   Primitive_SetLocation(gate_tris[1], world_l);
   Primitive_SetOrientation(gate_tris[1], start_o);
   Vector3 local_r = Vector3_Create((gate_width / 2.0f), 0.0f, 0.0f);
   Vector3 world_r = start_p + Vector3_RotateWithQuaternion(local_r, start_o);
   Primitive_SetLocation(gate_tris[2], world_r);
   Primitive_SetOrientation(gate_tris[2], start_o);
   Primitive_SetLocation(gate_tris[3], world_r);
   Primitive_SetOrientation(gate_tris[3], start_o);
   Vector3 local_b = Vector3_Create(0.0f, ((post_height / 2.0f) + (bar_height / 2.0f)), 0.0f);
   Vector3 world_b = start_p + Vector3_RotateWithQuaternion(local_b, start_o);
   Primitive_SetLocation(gate_tris[4], world_b);
   Primitive_SetOrientation(gate_tris[4], start_o);
   Primitive_SetLocation(gate_tris[5], world_b);
   Primitive_SetOrientation(gate_tris[5], start_o);
   Vector3 end_p = Spline_GetLocationAtTime(path, 1.0f);
   Quaternion end_o = Spline_GetOrientationAtTime(path, 1.0f, 0.0f, 0.25f);
   Vector3 local_lf = Vector3_Create((-gate_width / 2.0f), 0.0f, 0.0f);
   Vector3 world_lf = end_p + Vector3_RotateWithQuaternion(local_lf, end_o);
   Primitive_SetLocation(gate_tris[6], world_lf);
   Primitive_SetOrientation(gate_tris[6], end_o);
   Primitive_SetLocation(gate_tris[7], world_lf);
   Primitive_SetOrientation(gate_tris[7], end_o);
   Vector3 local_rf = Vector3_Create((gate_width / 2.0f), 0.0f, 0.0f);
   Vector3 world_rf = end_p + Vector3_RotateWithQuaternion(local_rf, end_o);
   Primitive_SetLocation(gate_tris[8], world_rf);
   Primitive_SetOrientation(gate_tris[8], end_o);
   Primitive_SetLocation(gate_tris[9], world_rf);
   Primitive_SetOrientation(gate_tris[9], end_o);
   Vector3 local_bf = Vector3_Create(0.0f, ((post_height / 2.0f) + (bar_height / 2.0f)), 0.0f);
   Vector3 world_bf = end_p + Vector3_RotateWithQuaternion(local_bf, end_o);
   Primitive_SetLocation(gate_tris[10], world_bf);
   Primitive_SetOrientation(gate_tris[10], end_o);
   Primitive_SetLocation(gate_tris[11], world_bf);
   Primitive_SetOrientation(gate_tris[11], end_o);
   for (i = 0; i < 6; i = (i + 1)) {
      float letter_x = (-12.5f + (5.0f * (float)i));
      Vector3 local = Vector3_Create(letter_x, 16.0f, 0.0f);
      Vector3 world = end_p + Vector3_RotateWithQuaternion(local, end_o);
      int start_tri = letter_tri_starts[i];
      int count = letter_tri_counts[i];
      int m;
      for (m = 0; m < count; m = (m + 1)) {
         int idx = (start_tri + m);
         Primitive_SetLocation(finish_text_tris[idx], world);
         Primitive_SetOrientation(finish_text_tris[idx], end_o);
      }
   }
}