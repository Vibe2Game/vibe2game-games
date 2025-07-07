bool sceneCreated;
Box cubeRed;
Box cubeYellow;
Box cubeBlue;
Material cubeRedMaterial;
Material cubeYellowMaterial;
Material cubeBlueMaterial;
PointLight keyLight;
PointLight fillLight;
PointLight backLight;
Text sequenceText;
int sequence[10];
int sequenceLength;
int currentStep;
float shakeStartTime;
int shakingCube;
bool waitingForInput;
int inputStep;
int tappedCubes[10];
Text gameOverText;
float tapShakeStartTime;
int tapShakingCube;
Text greatText;
float delayStartTime;
bool inDelay;

void GenerateSequence() {
   int i;
   for (i = 0; i < sequenceLength; i = i + 1) {
      sequence[i] = Int_Randomize(0, 2);
   }
}

void Game_Update() {
   if (Game_IsInitializing()) {
      Randomizer_SetDeterministicSeed(42);
      sceneCreated = true;
      cubeRed = Primitive_CreateBox();
      cubeYellow = Primitive_CreateBox();
      cubeBlue = Primitive_CreateBox();
      cubeRedMaterial = Material_Create();
      cubeYellowMaterial = Material_Create();
      cubeBlueMaterial = Material_Create();
      keyLight = PointLight_Create(0.0f);
      fillLight = PointLight_Create(0.0f);
      backLight = PointLight_Create(0.0f);
      sequenceText = Primitive_CreateText("Sequence: (#0.0)");
      gameOverText = Primitive_CreateText("Game Over");
      greatText = Primitive_CreateText("Great!");
      sequenceLength = 3;
      currentStep = 0;
      shakeStartTime = -1.0f;
      shakingCube = -1;
      waitingForInput = false;
      inputStep = 0;
      tapShakeStartTime = -1.0f;
      tapShakingCube = -1;
      delayStartTime = -1.0f;
      inDelay = false;
      Primitive_SetBoxDimensions(cubeRed, Vector3_Create(1.0f, 1.0f, 1.0f));
      Primitive_SetBoxCornerRadius(cubeRed, 0.2f);
      Primitive_SetLocation(cubeRed, Vector3_Create(1.5f, 0.0f, 0.866f));
      Material_SetColor(cubeRedMaterial, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
      Material_SetGlossiness(cubeRedMaterial, 0.25f);
      Primitive_SetMaterial(cubeRed, cubeRedMaterial);
      Primitive_SetBoxDimensions(cubeYellow, Vector3_Create(1.0f, 1.0f, 1.0f));
      Primitive_SetBoxCornerRadius(cubeYellow, 0.2f);
      Primitive_SetLocation(cubeYellow, Vector3_Create(-1.5f, 0.0f, 0.866f));
      Material_SetColor(cubeYellowMaterial, Color_Create(1.0f, 1.0f, 0.0f, 1.0f));
      Material_SetGlossiness(cubeYellowMaterial, 0.25f);
      Primitive_SetMaterial(cubeYellow, cubeYellowMaterial);
      Primitive_SetBoxDimensions(cubeBlue, Vector3_Create(1.0f, 1.0f, 1.0f));
      Primitive_SetBoxCornerRadius(cubeBlue, 0.2f);
      Primitive_SetLocation(cubeBlue, Vector3_Create(0.0f, 0.0f, -1.732f));
      Material_SetColor(cubeBlueMaterial, Color_Create(0.0f, 0.0f, 1.0f, 1.0f));
      Material_SetGlossiness(cubeBlueMaterial, 0.25f);
      Primitive_SetMaterial(cubeBlue, cubeBlueMaterial);
      Primitive_SetTextSize(sequenceText, 0.5f, 0.2f);
      Primitive_SetLocation(sequenceText, Vector3_Create(0.0f, 0.9f, 0.0f));
      Primitive_SetTextColor(sequenceText, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(sequenceText, Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(sequenceText, 8);
      Primitive_SetTextBackdropBlur(sequenceText, 8);
      Primitive_SetTextNumber(sequenceText, 0, (float)sequenceLength);
      Primitive_SetTextSize(gameOverText, 0.8f, 0.3f);
      Primitive_SetLocation(gameOverText, Vector3_Create(0.0f, 0.0f, 0.0f));
      Primitive_SetTextColor(gameOverText, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
      Primitive_SetTextBackgroundColor(gameOverText, Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(gameOverText, 8);
      Primitive_SetTextBackdropBlur(gameOverText, 8);
      Primitive_SetInvisible(gameOverText, true);
      Primitive_SetTextSize(greatText, 0.8f, 0.3f);
      Primitive_SetLocation(greatText, Vector3_Create(0.0f, 0.0f, 0.0f));
      Primitive_SetTextColor(greatText, Color_Create(0.0f, 1.0f, 0.0f, 1.0f));
      Primitive_SetTextBackgroundColor(greatText, Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
      Primitive_SetTextCornerRadius(greatText, 8);
      Primitive_SetTextBackdropBlur(greatText, 8);
      Primitive_SetInvisible(greatText, true);
      AmbientLight_Set(Color_Create(0.05f, 0.05f, 0.05f, 1.0f));
      Environment_SetGradient(Color_Create(0.10f, 0.10f, 0.10f, 1.0f), Color_Create(0.025f, 0.025f, 0.025f, 1.0f), Color_Create(0.01f, 0.01f, 0.01f, 1.0f), Color_Create(0.0f, 0.0f, 0.0f, 1.0f), 0.33f, 0.66f);
      PointLight_SetLocation(keyLight, Vector3_Create(-1.5f, 1.5f, 1.0f));
      PointLight_SetColor(keyLight, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      PointLight_SetEmissivityRange(keyLight, 2.5f);
      PointLight_SetLocation(fillLight, Vector3_Create(1.2f, 1.2f, 0.8f));
      PointLight_SetColor(fillLight, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      PointLight_SetEmissivityRange(fillLight, 2.5f);
      PointLight_SetLocation(backLight, Vector3_Create(0.0f, 1.8f, -1.5f));
      PointLight_SetColor(backLight, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      PointLight_SetEmissivityRange(backLight, 2.5f);
      View_SetMode(2);
      View_InitOrbit(30.0f, 45.0f, 5.0f);
      View_SetLookAtLocation(Vector3_Create(0.0f, 0.0f, 0.0f));
      View_SetFieldOfViewAngle(60.0f);
      View_SetClipPlanes(0.1f, 50.0f);
      View_SetZoomSensitivity(5.0f);
      GenerateSequence();
   }
   float t = Game_GetTime();
   if ((waitingForInput == false) && (currentStep < sequenceLength) && (inDelay == false)) {
      if ((shakeStartTime < 0.0f) || (t - shakeStartTime > 1.0f)) {
         if (shakeStartTime >= 0.0f) {
            if (shakingCube == cubeRed) {
               Primitive_SetLocation(cubeRed, Vector3_Create(1.5f, 0.0f, 0.866f));
            } else if (shakingCube == cubeYellow) {
               Primitive_SetLocation(cubeYellow, Vector3_Create(-1.5f, 0.0f, 0.866f));
            } else if (shakingCube == cubeBlue) {
               Primitive_SetLocation(cubeBlue, Vector3_Create(0.0f, 0.0f, -1.732f));
            }
            currentStep = currentStep + 1;
            if (currentStep == sequenceLength) {
               waitingForInput = true;
               inputStep = 0;
            }
         }
         if (currentStep < sequenceLength) {
            shakeStartTime = t;
            if (sequence[currentStep] == 0) {
               shakingCube = cubeRed;
            } else if (sequence[currentStep] == 1) {
               shakingCube = cubeYellow;
            } else {
               shakingCube = cubeBlue;
            }
         }
      }
   }
   if ((shakeStartTime >= 0.0f) && (t - shakeStartTime <= 1.0f)) {
      float shakeTime = t - shakeStartTime;
      float amplitude = 0.1f * (1.0f - shakeTime);
      float frequency = 20.0f;
      float offset;
      if (((int)(shakeTime * frequency) % 2) == 0) {
         offset = amplitude;
      } else {
         offset = -amplitude;
      }
      Vector3 basePos;
      if (shakingCube == cubeRed) {
         basePos = Vector3_Create(1.5f, 0.0f, 0.866f);
         Primitive_SetLocation(cubeRed, Vector3_Create(basePos.x + offset, basePos.y, basePos.z));
      } else if (shakingCube == cubeYellow) {
         basePos = Vector3_Create(-1.5f, 0.0f, 0.866f);
         Primitive_SetLocation(cubeYellow, Vector3_Create(basePos.x + offset, basePos.y, basePos.z));
      } else if (shakingCube == cubeBlue) {
         basePos = Vector3_Create(0.0f, 0.0f, -1.732f);
         Primitive_SetLocation(cubeBlue, Vector3_Create(basePos.x + offset, basePos.y, basePos.z));
      }
   }
   if (waitingForInput && Mouse_Click()) {
      int clicked = Clicked_GetPrimitive();
      if ((clicked >= 0) && Primitive_IsBox(clicked)) {
         tapShakeStartTime = t;
         tapShakingCube = clicked;
         int tappedCube;
         if (clicked == cubeRed) {
            tappedCube = 0;
         } else if (clicked == cubeYellow) {
            tappedCube = 1;
         } else {
            tappedCube = 2;
         }
         tappedCubes[inputStep] = tappedCube;
         inputStep = inputStep + 1;
         if (inputStep == sequenceLength) {
            bool correct = true;
            int i;
            for (i = 0; i < sequenceLength; i = i + 1) {
               if (tappedCubes[i] != sequence[i]) {
                  correct = false;
               }
            }
            if (correct) {
               Primitive_SetInvisible(greatText, false);
               delayStartTime = t;
               inDelay = true;
            } else {
               Primitive_SetInvisible(gameOverText, false);
               Primitive_SetInvisible(cubeRed, true);
               Primitive_SetInvisible(cubeYellow, true);
               Primitive_SetInvisible(cubeBlue, true);
               Primitive_SetInvisible(sequenceText, true);
            }
         }
      }
   }
   if ((inDelay) && (t - delayStartTime > 2.0f)) {
      Primitive_SetInvisible(greatText, true);
      sequenceLength = sequenceLength + 1;
      if (sequenceLength > 10) {
         sequenceLength = 10;
      }
      Primitive_SetTextNumber(sequenceText, 0, (float)sequenceLength);
      currentStep = 0;
      shakeStartTime = -1.0f;
      waitingForInput = false;
      inDelay = false;
      GenerateSequence();
   }
   if ((tapShakeStartTime >= 0.0f) && (t - tapShakeStartTime <= 1.0f)) {
      float shakeTime = t - tapShakeStartTime;
      float amplitude = 0.1f * (1.0f - shakeTime);
      float frequency = 20.0f;
      float offset;
      if (((int)(shakeTime * frequency) % 2) == 0) {
         offset = amplitude;
      } else {
         offset = -amplitude;
      }
      Vector3 basePos;
      if (tapShakingCube == cubeRed) {
         basePos = Vector3_Create(1.5f, 0.0f, 0.866f);
         Primitive_SetLocation(cubeRed, Vector3_Create(basePos.x + offset, basePos.y, basePos.z));
      } else if (tapShakingCube == cubeYellow) {
         basePos = Vector3_Create(-1.5f, 0.0f, 0.866f);
         Primitive_SetLocation(cubeYellow, Vector3_Create(basePos.x + offset, basePos.y, basePos.z));
      } else if (tapShakingCube == cubeBlue) {
         basePos = Vector3_Create(0.0f, 0.0f, -1.732f);
         Primitive_SetLocation(cubeBlue, Vector3_Create(basePos.x + offset, basePos.y, basePos.z));
      }
   } else if ((tapShakeStartTime >= 0.0f) && (t - tapShakeStartTime > 1.0f)) {
      if (tapShakingCube == cubeRed) {
         Primitive_SetLocation(cubeRed, Vector3_Create(1.5f, 0.0f, 0.866f));
      } else if (tapShakingCube == cubeYellow) {
         Primitive_SetLocation(cubeYellow, Vector3_Create(-1.5f, 0.0f, 0.866f));
      } else if (tapShakingCube == cubeBlue) {
         Primitive_SetLocation(cubeBlue, Vector3_Create(0.0f, 0.0f, -1.732f));
      }
      tapShakeStartTime = -1.0f;
      tapShakingCube = -1;
   }
}