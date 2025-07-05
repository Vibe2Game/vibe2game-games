bool isShooting;
float lastShotTime;
float bulletSpeeds[40];
Sphere bullets[40];
int bulletIndex;
Material bulletMaterial;
Box playerBox;
Material playerBoxMaterial;
bool isDragging;
float boxXPosition;
Box enemyBoxes[200];
Material enemyMaterial;
float enemySpeeds[200];
float dragStartX;
float boxStartX;
void UpdateBullet(int index, float deltaTime) {
   Vector3 bulletPos = Primitive_GetLocation(bullets[index]);
   bulletPos.z = bulletPos.z - (bulletSpeeds[index] * deltaTime);
   Primitive_SetLocation(bullets[index], bulletPos);
   for (int i = 0; i < 200; i++) {
      if (enemySpeeds[i] > 0.0f) {
         if (Collision_Check(bullets[index], enemyBoxes[i], 0)) {
            Primitive_SetInvisible(bullets[index], true);
            bulletSpeeds[index] = 0.0f;
            Primitive_SetInvisible(enemyBoxes[i], true);
            enemySpeeds[i] = 0.0f;
         }
      }
   }
}
void ShootBullet() {
   Vector3 direction = Vector3_Create(0.0f, 0.0f, 1.0f);
   bulletSpeeds[bulletIndex] = 5.0f;
   Primitive_SetLocation(bullets[bulletIndex], Vector3_Create(boxXPosition, 0.0f, 0.0f));
   Primitive_SetInvisible(bullets[bulletIndex], false);
   bulletIndex = bulletIndex + 1;
   if (bulletIndex >= 40) {
      bulletIndex = 0;
   }
}
void UpdateEnemy(int index, float deltaTime) {
   Vector3 pos = Primitive_GetLocation(enemyBoxes[index]);
   pos.z = pos.z + (enemySpeeds[index] * deltaTime);
   Primitive_SetLocation(enemyBoxes[index], pos);
}
void Game_Update() {
   if (Game_IsInitializing()) {
      isShooting = false;
      lastShotTime = 0.0f;
      bulletIndex = 0;
      isDragging = false;
      boxXPosition = 0.0f;
      dragStartX = 0.0f;
      boxStartX = 0.0f;
      bulletMaterial = Material_Create();
      Material_SetColor(bulletMaterial, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
      Material_SetGlossiness(bulletMaterial, 0.5f);
      for (int i = 0; i < 40; i++) {
         bullets[i] = Primitive_CreateSphere();
         Primitive_SetSphereRadius(bullets[i], 0.025f);
         Primitive_SetMaterial(bullets[i], bulletMaterial);
         Primitive_SetInvisible(bullets[i], true);
         bulletSpeeds[i] = 0.0f;
      }
      playerBox = Primitive_CreateBox();
      Primitive_SetBoxDimensions(playerBox, Vector3_Create(0.2f, 0.2f, 0.2f));
      Primitive_SetBoxCornerRadius(playerBox, 0.05f);
      playerBoxMaterial = Material_Create();
      Material_SetColor(playerBoxMaterial, Color_Create(0.0f, 1.0f, 0.0f, 1.0f));
      Material_SetGlossiness(playerBoxMaterial, 0.25f);
      Primitive_SetMaterial(playerBox, playerBoxMaterial);
      Primitive_SetLocation(playerBox, Vector3_Create(0.0f, 0.0f, 0.0f));
      enemyMaterial = Material_Create();
      Material_SetColor(enemyMaterial, Color_Create(0.0f, 0.0f, 1.0f, 1.0f));
      Material_SetGlossiness(enemyMaterial, 0.25f);
      Randomizer_SetDeterministicSeed(42);
      for (int i = 0; i < 200; i++) {
         enemyBoxes[i] = Primitive_CreateBox();
         Primitive_SetBoxDimensions(enemyBoxes[i], Vector3_Create(0.2f, 0.2f, 0.2f));
         Primitive_SetMaterial(enemyBoxes[i], enemyMaterial);
         float xPos = Float_RandomizeDeterministic(-1.0f, 1.0f);
         Primitive_SetLocation(enemyBoxes[i], Vector3_Create(xPos, 0.0f, -5.0f - ((float)i * 0.1f)));
         enemySpeeds[i] = Float_RandomizeDeterministic(0.5f, 2.0f);
      }
      View_SetMode(0);
      View_SetTargetLocation(Vector3_Create(0.0f, 2.0f, 1.5f));
      View_SetLookAtLocation(Vector3_Create(0.0f, 0.0f, -1.5f));
      View_SetResponse(1.0f, 1.0f);
      View_SetLockCameraRoll(1);
      View_SetFieldOfViewAngle(50.0f);
      AmbientLight_Set(Color_Create(0.1f, 0.1f, 0.1f, 1.0f));
      Environment_SetGradient(Color_Create(0.8f, 0.8f, 0.8f, 1.0f), Color_Create(0.4f, 0.4f, 0.4f, 1.0f), Color_Create(0.2f, 0.2f, 0.2f, 1.0f), Color_Create(0.1f, 0.1f, 0.1f, 1.0f), 0.33f, 0.66f);
      PointLight keyLight = PointLight_Create(0.0f);
      PointLight_SetLocation(keyLight, Vector3_Create(-1.5f, 1.5f, 1.0f));
      PointLight_SetColor(keyLight, Color_Create(0.75f, 0.75f, 0.75f, 1.0f));
      PointLight_SetEmissivityRange(keyLight, 20.0f);
      PointLight fillLight = PointLight_Create(0.0f);
      PointLight_SetLocation(fillLight, Vector3_Create(1.2f, 1.2f, 0.8f));
      PointLight_SetColor(fillLight, Color_Create(0.35f, 0.35f, 0.35f, 1.0f));
      PointLight_SetEmissivityRange(fillLight, 30.0f);
   }
   float currentTime = Game_GetTime();
   float deltaTime = Game_GetTick();
   if (Mouse_Down()) {
      if (!isDragging) {
         isDragging = true;
         dragStartX = Mouse_X();
         boxStartX = boxXPosition;
      }
      if (isDragging) {
         float mouseX = Mouse_X();
         boxXPosition = boxStartX + ((mouseX - dragStartX) * 2.0f);
         if (boxXPosition < -1.0f) {
            boxXPosition = -1.0f;
         }
         if (boxXPosition > 1.0f) {
            boxXPosition = 1.0f;
         }
         Primitive_SetLocation(playerBox, Vector3_Create(boxXPosition, 0.0f, 0.0f));
      }
      if (currentTime - lastShotTime >= 0.1f) {
         isShooting = true;
         lastShotTime = currentTime;
      } else {
         isShooting = false;
      }
      if (isShooting) {
         ShootBullet();
      }
   } else {
      isDragging = false;
      isShooting = false;
   }
   for (int i = 0; i < 40; i++) {
      if (bulletSpeeds[i] > 0.0f) {
         UpdateBullet(i, deltaTime);
      }
   }
   for (int i = 0; i < 200; i++) {
      if (enemySpeeds[i] > 0.0f) {
         UpdateEnemy(i, deltaTime);
      }
   }
}
