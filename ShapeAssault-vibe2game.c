bool isShooting;
float lastShotTime;
float bulletSpeeds[50];
Sphere bullets[50];
Vector3 bulletDirections[50];
int bulletIndex;
Material bulletMaterial;
Cylinder playerBase;
Box playerCannon;
Material playerMaterial;
bool isDragging;
float boxXPosition;
Sphere enemyEllipsoids[150];
Cylinder enemyCylinders[150];
Box enemyBoxes[150];
Material slowEnemyMaterial;
Material fastEnemyMaterial;
Material jumpingEnemyMaterial;
float enemySpeeds[150];
float enemyWeaveTimers[150];
float enemyWeaveAmplitudes[150];
float enemyBaseXPositions[150];
float enemyJumpTimers[150];
float enemyJumpHeights[150];
bool enemyIsJumping[150];
bool enemyIsWeaving[150];
bool enemyCanJump[150];
float dragStartX;
float boxStartX;
Text scoreText;
Text bestScoreText;
Text gameOverText;
Text playAgainButton;
Text levelCompleteText;
Text continueButton;
int score;
int bestScore;
bool gameOver;
bool levelComplete;
Box bonusBox;
Material bonusMaterial;
float bonusSpeed;
bool bonusActive;
bool doubleFiring;
Box floorTiles[104];
Material floorMaterial;
Text scoreLabels[5];
float labelTimes[5];
bool labelVisible[5];
Vector3 labelPositions[5];
float labelScores[5];
int labelIndex;

void UpdateBullet(int index, float deltaTime, float currentTime) {
    Vector3 bulletPos = Primitive_GetLocation(bullets[index]);
    bulletPos = bulletPos + (bulletDirections[index] * (bulletSpeeds[index] * deltaTime));
    Primitive_SetLocation(bullets[index], bulletPos);
    for (int i = 0; i < 150; i++) {
        if (enemySpeeds[i] > 0.0f) {
            if (enemyCanJump[i]) {
                if (Collision_Check(bullets[index], enemyEllipsoids[i], 0)) {
                    Primitive_SetInvisible(bullets[index], true);
                    bulletSpeeds[index] = 0.0f;
                    Primitive_SetInvisible(enemyEllipsoids[i], true);
                    enemySpeeds[i] = 0.0f;
                    float scoreAdded;
                    if (enemyIsJumping[i]) {
                        scoreAdded = 10.0f;
                        score = score + 10;
                    } else {
                        scoreAdded = 5.0f;
                        score = score + 5;
                    }
                    Primitive_SetTextNumber(scoreText, 0, (float)score);
                    Vector3 enemyPos = Primitive_GetLocation(enemyEllipsoids[i]);
                    labelPositions[labelIndex] = enemyPos + Vector3_Create(0.0f, 0.1f, 0.0f);
                    labelScores[labelIndex] = scoreAdded;
                    Primitive_SetTextNumber(scoreLabels[labelIndex], 0, scoreAdded);
                    labelTimes[labelIndex] = currentTime;
                    labelVisible[labelIndex] = true;
                    labelIndex = (labelIndex + 1) % 5;
                }
            } else if (enemySpeeds[i] > 2.0f) {
                if (Collision_Check(bullets[index], enemyCylinders[i], 0)) {
                    Primitive_SetInvisible(bullets[index], true);
                    bulletSpeeds[index] = 0.0f;
                    Primitive_SetInvisible(enemyCylinders[i], true);
                    enemySpeeds[i] = 0.0f;
                    float scoreAdded = 8.0f;
                    score = score + 8;
                    Primitive_SetTextNumber(scoreText, 0, (float)score);
                    Vector3 enemyPos = Primitive_GetLocation(enemyCylinders[i]);
                    labelPositions[labelIndex] = enemyPos + Vector3_Create(0.0f, 0.1f, 0.0f);
                    labelScores[labelIndex] = scoreAdded;
                    Primitive_SetTextNumber(scoreLabels[labelIndex], 0, scoreAdded);
                    labelTimes[labelIndex] = currentTime;
                    labelVisible[labelIndex] = true;
                    labelIndex = (labelIndex + 1) % 5;
                }
            } else {
                if (Collision_Check(bullets[index], enemyBoxes[i], 0)) {
                    Primitive_SetInvisible(bullets[index], true);
                    bulletSpeeds[index] = 0.0f;
                    Primitive_SetInvisible(enemyBoxes[i], true);
                    enemySpeeds[i] = 0.0f;
                    float scoreAdded = 2.0f;
                    score = score + 2;
                    Primitive_SetTextNumber(scoreText, 0, (float)score);
                    Vector3 enemyPos = Primitive_GetLocation(enemyBoxes[i]);
                    labelPositions[labelIndex] = enemyPos + Vector3_Create(0.0f, 0.1f, 0.0f);
                    labelScores[labelIndex] = scoreAdded;
                    Primitive_SetTextNumber(scoreLabels[labelIndex], 0, scoreAdded);
                    labelTimes[labelIndex] = currentTime;
                    labelVisible[labelIndex] = true;
                    labelIndex = (labelIndex + 1) % 5;
                }
            }
        }
    }
    if (bonusActive) {
        if (Collision_Check(bullets[index], bonusBox, 0)) {
            Primitive_SetInvisible(bullets[index], true);
            bulletSpeeds[index] = 0.0f;
            Primitive_SetInvisible(bonusBox, true);
            bonusActive = false;
            doubleFiring = true;
        }
    }
}

void ShootBullet() {
    Vector3 direction = Vector3_Create(0.0f, 0.0f, -1.0f);
    bulletSpeeds[bulletIndex] = 6.0f;
    Primitive_SetLocation(bullets[bulletIndex], Vector3_Create(boxXPosition, 0.05f, -0.1f));
    Primitive_SetInvisible(bullets[bulletIndex], false);
    bulletDirections[bulletIndex] = direction;
    bulletIndex = (bulletIndex + 1) % 50;
    if (doubleFiring) {
        float angle = Float_RandomizeDeterministic(-0.523599f, 0.523599f);
        Quaternion rotation = Quaternion_CreateFromAxisAngle(Vector3_Create(0.0f, 1.0f, 0.0f), angle);
        Vector3 extraDirection = Vector3_RotateWithQuaternion(direction, rotation);
        bulletSpeeds[bulletIndex] = 6.0f;
        Primitive_SetLocation(bullets[bulletIndex], Vector3_Create(boxXPosition, 0.05f, -0.1f));
        Primitive_SetInvisible(bullets[bulletIndex], false);
        bulletDirections[bulletIndex] = extraDirection;
        bulletIndex = (bulletIndex + 1) % 50;
    }
}

void UpdateEnemy(int index, float deltaTime) {
    Vector3 pos;
    if (enemyCanJump[index]) {
        pos = Primitive_GetLocation(enemyEllipsoids[index]);
    } else if (enemySpeeds[index] > 2.0f) {
        pos = Primitive_GetLocation(enemyCylinders[index]);
    } else {
        pos = Primitive_GetLocation(enemyBoxes[index]);
    }
    pos.z = pos.z + (enemySpeeds[index] * deltaTime);
    if (enemyIsWeaving[index]) {
        enemyWeaveTimers[index] = enemyWeaveTimers[index] + deltaTime;
        float weavePhase = 2.0f * 3.141593f * enemyWeaveTimers[index] / 2.0f;
        float maxAmplitude = 1.2f - Float_Abs(enemyBaseXPositions[index]);
        if (enemyWeaveAmplitudes[index] > maxAmplitude) {
            enemyWeaveAmplitudes[index] = maxAmplitude;
        }
        pos.x = enemyBaseXPositions[index] + (enemyWeaveAmplitudes[index] * Float_Sin(weavePhase));
    }
    if (enemyCanJump[index] && !enemyIsJumping[index]) {
        enemyJumpTimers[index] = enemyJumpTimers[index] + deltaTime;
        if (enemyJumpTimers[index] > 3.0f && Float_RandomizeDeterministic(0.0f, 1.0f) > 0.8f) {
            enemyIsJumping[index] = true;
            enemyJumpTimers[index] = 0.0f;
            enemyJumpHeights[index] = Float_RandomizeDeterministic(0.5f, 0.9f);
        }
    }
    if (enemyIsJumping[index]) {
        enemyJumpTimers[index] = enemyJumpTimers[index] + deltaTime;
        float t = enemyJumpTimers[index] / 0.8f;
        if (t <= 1.0f) {
            float progress = 4.0f * t * (1.0f - t);
            pos.y = enemyJumpHeights[index] * progress;
        } else {
            pos.y = 0.0f;
            enemyIsJumping[index] = false;
            enemyJumpTimers[index] = 0.0f;
        }
    }
    if (enemyCanJump[index]) {
        Primitive_SetLocation(enemyEllipsoids[index], pos);
    } else if (enemySpeeds[index] > 2.0f) {
        Primitive_SetLocation(enemyCylinders[index], pos);
    } else {
        Primitive_SetLocation(enemyBoxes[index], pos);
    }
}

void UpdateBonus(float deltaTime) {
    if (bonusActive) {
        Vector3 pos = Primitive_GetLocation(bonusBox);
        pos.x = pos.x + (bonusSpeed * deltaTime);
        if (pos.x > 1.2f || pos.x < -1.2f) {
            bonusSpeed = -bonusSpeed;
            pos.x = pos.x + (bonusSpeed * deltaTime);
        }
        Primitive_SetLocation(bonusBox, pos);
    }
}

void ResetGame() {
    isShooting = false;
    lastShotTime = 0.0f;
    bulletIndex = 0;
    isDragging = false;
    boxXPosition = 0.0f;
    dragStartX = 0.0f;
    boxStartX = 0.0f;
    score = 0;
    gameOver = false;
    levelComplete = false;
    doubleFiring = false;
    for (int i = 0; i < 50; i++) {
        Primitive_SetInvisible(bullets[i], true);
        bulletSpeeds[i] = 0.0f;
    }
    Primitive_SetInvisible(playerBase, false);
    Primitive_SetInvisible(playerCannon, false);
    Primitive_SetLocation(playerBase, Vector3_Create(0.0f, 0.0f, 0.0f));
    Primitive_SetLocation(playerCannon, Vector3_Create(0.0f, 0.05f, -0.05f));
    Randomizer_SetDeterministicSeed(42);
    for (int i = 0; i < 150; i++) {
        float xPos = Float_RandomizeDeterministic(-1.2f, 1.2f);
        Primitive_SetInvisible(enemyEllipsoids[i], true);
        Primitive_SetInvisible(enemyCylinders[i], true);
        Primitive_SetInvisible(enemyBoxes[i], true);
        Primitive_SetLocation(enemyEllipsoids[i], Vector3_Create(xPos, 0.0f, -4.0f - ((float)i * 0.1f)));
        Primitive_SetLocation(enemyCylinders[i], Vector3_Create(xPos, 0.0f, -4.0f - ((float)i * 0.1f)));
        Primitive_SetLocation(enemyBoxes[i], Vector3_Create(xPos, 0.0f, -4.0f - ((float)i * 0.1f)));
        enemySpeeds[i] = Float_RandomizeDeterministic(0.6f, 3.0f);
        enemyWeaveTimers[i] = Float_RandomizeDeterministic(0.0f, 2.0f);
        enemyWeaveAmplitudes[i] = Float_RandomizeDeterministic(0.1f, 0.5f);
        enemyBaseXPositions[i] = xPos;
        enemyJumpTimers[i] = Float_RandomizeDeterministic(0.0f, 3.0f);
        enemyJumpHeights[i] = 0.0f;
        enemyIsJumping[i] = false;
        enemyIsWeaving[i] = false;
        enemyCanJump[i] = false;
        if (Float_RandomizeDeterministic(0.0f, 1.0f) > 0.7f) {
            Primitive_SetMaterial(enemyEllipsoids[i], jumpingEnemyMaterial);
            Primitive_SetInvisible(enemyEllipsoids[i], false);
            enemyCanJump[i] = true;
        } else if (enemySpeeds[i] > 2.0f) {
            Primitive_SetMaterial(enemyCylinders[i], fastEnemyMaterial);
            Primitive_SetInvisible(enemyCylinders[i], false);
        } else {
            Primitive_SetMaterial(enemyBoxes[i], slowEnemyMaterial);
            Primitive_SetInvisible(enemyBoxes[i], false);
            enemyIsWeaving[i] = true;
        }
    }
    float xPos = Float_RandomizeDeterministic(-1.0f, 1.0f);
    float zPos = Float_RandomizeDeterministic(-5.0f, -2.0f);
    Primitive_SetLocation(bonusBox, Vector3_Create(xPos, 0.0f, zPos));
    bonusSpeed = Float_RandomizeDeterministic(-1.5f, 1.5f);
    if (bonusSpeed == 0.0f) {
        bonusSpeed = 1.5f;
    }
    Primitive_SetInvisible(bonusBox, false);
    bonusActive = true;
    Primitive_SetTextNumber(scoreText, 0, (float)score);
    Primitive_SetInvisible(gameOverText, true);
    Primitive_SetInvisible(playAgainButton, true);
    Primitive_SetInvisible(levelCompleteText, true);
    Primitive_SetInvisible(continueButton, true);
    for (int i = 0; i < 5; i++) {
        Primitive_SetInvisible(scoreLabels[i], true);
        labelVisible[i] = false;
    }
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
        score = 0;
        bestScore = 0;
        gameOver = false;
        levelComplete = false;
        doubleFiring = false;
        bulletMaterial = Material_Create();
        Material_SetColor(bulletMaterial, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
        Material_SetGlossiness(bulletMaterial, 0.5f);
        for (int i = 0; i < 50; i++) {
            bullets[i] = Primitive_CreateSphere();
            Primitive_SetSphereRadius(bullets[i], 0.02f);
            Primitive_SetMaterial(bullets[i], bulletMaterial);
            Primitive_SetInvisible(bullets[i], true);
            bulletSpeeds[i] = 0.0f;
        }
        playerBase = Primitive_CreateCylinder();
        Primitive_SetCylinderLength(playerBase, 0.1f);
        Primitive_SetCylinderRadii(playerBase, 0.075f, 0.075f);
        Primitive_SetOrientation(playerBase, Quaternion_CreateFromEulerAngles(0.0f, 0.0f, 1.570796f, 0));
        playerCannon = Primitive_CreateBox();
        Primitive_SetBoxDimensions(playerCannon, Vector3_Create(0.05f, 0.05f, 0.2f));
        playerMaterial = Material_Create();
        Material_SetColor(playerMaterial, Color_Create(0.3f, 0.3f, 0.3f, 1.0f));
        Material_SetGlossiness(playerMaterial, 2.5f);
        Primitive_SetMaterial(playerBase, playerMaterial);
        Primitive_SetMaterial(playerCannon, playerMaterial);
        Primitive_SetLocation(playerBase, Vector3_Create(0.0f, 0.0f, 0.0f));
        Primitive_SetLocation(playerCannon, Vector3_Create(0.0f, 0.05f, -0.05f));
        slowEnemyMaterial = Material_Create();
        Material_SetColor(slowEnemyMaterial, Color_Create(1.0f, 0.5f, 0.0f, 1.0f));
        Material_SetGlossiness(slowEnemyMaterial, 2.5f);
        fastEnemyMaterial = Material_Create();
        Material_SetColor(fastEnemyMaterial, Color_Create(0.0f, 0.0f, 1.0f, 1.0f));
        Material_SetGlossiness(fastEnemyMaterial, 0.25f);
        jumpingEnemyMaterial = Material_Create();
        Material_SetColor(jumpingEnemyMaterial, Color_Create(0.5f, 0.0f, 0.0f, 1.0f));
        Material_SetGlossiness(jumpingEnemyMaterial, 0.25f);
        bonusMaterial = Material_Create();
        Material_SetColor(bonusMaterial, Color_Create(0.0f, 0.0f, 0.0f, 1.0f));
        Material_SetGlossiness(bonusMaterial, 0.5f);
        floorMaterial = Material_Create();
        Material_SetColor(floorMaterial, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
        Material_SetGlossiness(floorMaterial, 0.25f);
        for (int i = 0; i < 104; i++) {
            int row = i / 4;
            int col = i % 4;
            float x = -1.125f + ((float)col * 0.75f);
            float z = -18.625f + ((float)row * 0.75f);
            floorTiles[i] = Primitive_CreateBox();
            Primitive_SetBoxDimensions(floorTiles[i], Vector3_Create(0.6f, 0.02f, 0.6f));
            Primitive_SetMaterial(floorTiles[i], floorMaterial);
            Primitive_SetLocation(floorTiles[i], Vector3_Create(x, -0.1f, z));
        }
        Randomizer_SetDeterministicSeed(42);
        for (int i = 0; i < 150; i++) {
            float xPos = Float_RandomizeDeterministic(-1.2f, 1.2f);
            enemyEllipsoids[i] = Primitive_CreateSphere();
            Primitive_SetSphereRadius(enemyEllipsoids[i], 0.075f);
            Primitive_SetSphereFlattening(enemyEllipsoids[i], 0.5f);
            enemyCylinders[i] = Primitive_CreateCylinder();
            Primitive_SetCylinderLength(enemyCylinders[i], 0.15f);
            Primitive_SetCylinderRadii(enemyCylinders[i], 0.075f, 0.075f);
            Primitive_SetCylinderCornerRadius(enemyCylinders[i], 0.02f);
            enemyBoxes[i] = Primitive_CreateBox();
            Primitive_SetBoxDimensions(enemyBoxes[i], Vector3_Create(0.1f, 0.1f, 0.1f));
            Primitive_SetBoxCornerRadius(enemyBoxes[i], 0.03f);
            Primitive_SetInvisible(enemyEllipsoids[i], true);
            Primitive_SetInvisible(enemyCylinders[i], true);
            Primitive_SetInvisible(enemyBoxes[i], true);
            Primitive_SetLocation(enemyEllipsoids[i], Vector3_Create(xPos, 0.0f, -4.0f - ((float)i * 0.1f)));
            Primitive_SetLocation(enemyCylinders[i], Vector3_Create(xPos, 0.0f, -4.0f - ((float)i * 0.1f)));
            Primitive_SetLocation(enemyBoxes[i], Vector3_Create(xPos, 0.0f, -4.0f - ((float)i * 0.1f)));
            enemySpeeds[i] = Float_RandomizeDeterministic(0.6f, 3.0f);
            enemyWeaveTimers[i] = Float_RandomizeDeterministic(0.0f, 2.0f);
            enemyWeaveAmplitudes[i] = Float_RandomizeDeterministic(0.1f, 0.5f);
            enemyBaseXPositions[i] = xPos;
            enemyJumpTimers[i] = Float_RandomizeDeterministic(0.0f, 3.0f);
            enemyJumpHeights[i] = 0.0f;
            enemyIsJumping[i] = false;
            enemyIsWeaving[i] = false;
            enemyCanJump[i] = false;
            if (Float_RandomizeDeterministic(0.0f, 1.0f) > 0.7f) {
                Primitive_SetMaterial(enemyEllipsoids[i], jumpingEnemyMaterial);
                Primitive_SetInvisible(enemyEllipsoids[i], false);
                enemyCanJump[i] = true;
            } else if (enemySpeeds[i] > 2.0f) {
                Primitive_SetMaterial(enemyCylinders[i], fastEnemyMaterial);
                Primitive_SetInvisible(enemyCylinders[i], false);
            } else {
                Primitive_SetMaterial(enemyBoxes[i], slowEnemyMaterial);
                Primitive_SetInvisible(enemyBoxes[i], false);
                enemyIsWeaving[i] = true;
            }
        }
        bonusBox = Primitive_CreateBox();
        Primitive_SetBoxDimensions(bonusBox, Vector3_Create(0.1f, 0.1f, 0.1f));
        Primitive_SetBoxCornerRadius(bonusBox, 0.02f);
        Primitive_SetMaterial(bonusBox, bonusMaterial);
        float xPos = Float_RandomizeDeterministic(-1.0f, 1.0f);
        float zPos = Float_RandomizeDeterministic(-5.0f, -2.0f);
        Primitive_SetLocation(bonusBox, Vector3_Create(xPos, 0.0f, zPos));
        bonusSpeed = Float_RandomizeDeterministic(-1.5f, 1.5f);
        if (bonusSpeed == 0.0f) {
            bonusSpeed = 1.5f;
        }
        bonusActive = true;
        scoreText = Primitive_CreateText("Score: (#0.0)");
        Primitive_SetTextFont(scoreText, 10);
        Primitive_SetTextSize(scoreText, 0.5f, 0.1f);
        Primitive_SetTextColor(scoreText, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
        Primitive_SetTextBackgroundColor(scoreText, Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
        Primitive_SetTextCornerRadius(scoreText, 5);
        Primitive_SetTextBackdropBlur(scoreText, 8);
        Primitive_SetLocation(scoreText, Vector3_Create(-0.725f, 0.925f, 0.0f));
        Primitive_SetTextNumber(scoreText, 0, (float)score);
        bestScoreText = Primitive_CreateText("Best: (#0.0)");
        Primitive_SetTextFont(bestScoreText, 10);
        Primitive_SetTextSize(bestScoreText, 0.5f, 0.1f);
        Primitive_SetTextColor(bestScoreText, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
        Primitive_SetTextBackgroundColor(bestScoreText, Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
        Primitive_SetTextCornerRadius(bestScoreText, 5);
        Primitive_SetTextBackdropBlur(bestScoreText, 8);
        Primitive_SetLocation(bestScoreText, Vector3_Create(0.725f, 0.925f, 0.0f));
        Primitive_SetTextNumber(bestScoreText, 0, (float)bestScore);
        gameOverText = Primitive_CreateText("Game Over!");
        Primitive_SetTextFont(gameOverText, 10);
        Primitive_SetTextSize(gameOverText, 0.8f, 0.2f);
        Primitive_SetTextColor(gameOverText, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
        Primitive_SetTextBackgroundColor(gameOverText, Color_Create(0.0f, 0.0f, 0.0f, 0.7f));
        Primitive_SetTextCornerRadius(gameOverText, 10);
        Primitive_SetTextBackdropBlur(gameOverText, 8);
        Primitive_SetLocation(gameOverText, Vector3_Create(0.0f, 0.0f, 0.0f));
        Primitive_SetInvisible(gameOverText, true);
        playAgainButton = Primitive_CreateText("Play Again");
        Primitive_SetTextFont(playAgainButton, 10);
        Primitive_SetTextSize(playAgainButton, 0.4f, 0.1f);
        Primitive_SetTextColor(playAgainButton, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
        Primitive_SetTextBackgroundColor(playAgainButton, Color_Create(0.0f, 0.0f, 1.0f, 0.7f));
        Primitive_SetTextCornerRadius(playAgainButton, 5);
        Primitive_SetTextBackdropBlur(playAgainButton, 8);
        Primitive_SetLocation(playAgainButton, Vector3_Create(0.0f, -0.8f, 0.0f));
        Primitive_SetInvisible(playAgainButton, true);
        levelCompleteText = Primitive_CreateText("Level Complete!");
        Primitive_SetTextFont(levelCompleteText, 10);
        Primitive_SetTextSize(levelCompleteText, 0.8f, 0.2f);
        Primitive_SetTextColor(levelCompleteText, Color_Create(0.0f, 1.0f, 0.0f, 1.0f));
        Primitive_SetTextBackgroundColor(levelCompleteText, Color_Create(0.0f, 0.0f, 0.0f, 0.7f));
        Primitive_SetTextCornerRadius(levelCompleteText, 10);
        Primitive_SetTextBackdropBlur(levelCompleteText, 8);
        Primitive_SetLocation(levelCompleteText, Vector3_Create(0.0f, 0.0f, 0.0f));
        Primitive_SetInvisible(levelCompleteText, true);
        continueButton = Primitive_CreateText("Continue");
        Primitive_SetTextFont(continueButton, 10);
        Primitive_SetTextSize(continueButton, 0.4f, 0.1f);
        Primitive_SetTextColor(continueButton, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
        Primitive_SetTextBackgroundColor(continueButton, Color_Create(0.0f, 0.0f, 1.0f, 0.7f));
        Primitive_SetTextCornerRadius(continueButton, 5);
        Primitive_SetTextBackdropBlur(continueButton, 8);
        Primitive_SetLocation(continueButton, Vector3_Create(0.0f, -0.8f, 0.0f));
        Primitive_SetInvisible(continueButton, true);
        for (int i = 0; i < 5; i++) {
            scoreLabels[i] = Primitive_CreateText("+ (#0.0)");
            Primitive_SetTextFont(scoreLabels[i], 10);
            Primitive_SetTextSize(scoreLabels[i], 0.2f, 0.1f);
            Primitive_SetTextColor(scoreLabels[i], Color_Create(0.0f, 1.0f, 0.0f, 1.0f));
            Primitive_SetTextBackgroundColor(scoreLabels[i], Color_Create(0.0f, 0.0f, 0.0f, 0.0f));
            Primitive_SetTextCornerRadius(scoreLabels[i], 0);
            Primitive_SetTextBackdropBlur(scoreLabels[i], 0);
            Primitive_SetInvisible(scoreLabels[i], true);
            labelVisible[i] = false;
        }
        labelIndex = 0;
        View_SetMode(0);
        View_SetTargetLocation(Vector3_Create(0.0f, 1.8f, 1.2f));
        View_SetLookAtLocation(Vector3_Create(0.0f, 0.0f, -1.2f));
        View_SetResponse(1.0f, 1.0f);
        View_SetLockCameraRoll(1);
        View_SetFieldOfViewAngle(55.0f);
        View_SetClipPlanes(0.1f, 100.0f);
        AmbientLight_Set(Color_Create(0.12f, 0.12f, 0.12f, 1.0f));
        Environment_SetGradient(Color_Create(0.85f, 0.85f, 0.85f, 1.0f), Color_Create(0.45f, 0.45f, 0.45f, 1.0f), Color_Create(0.25f, 0.25f, 0.25f, 1.0f), Color_Create(0.0f, 0.0f, 0.0f, 1.0f), 0.33f, 0.66f);
        PointLight keyLight = PointLight_Create(0.0f);
        PointLight_SetLocation(keyLight, Vector3_Create(-1.8f, 1.8f, 1.2f));
        PointLight_SetColor(keyLight, Color_Create(0.8f, 0.8f, 0.8f, 1.0f));
        PointLight_SetEmissivityRange(keyLight, 25.0f);
        PointLight fillLight = PointLight_Create(0.0f);
        PointLight_SetLocation(fillLight, Vector3_Create(1.5f, 1.5f, 1.0f));
        PointLight_SetColor(fillLight, Color_Create(0.4f, 0.4f, 0.4f, 1.0f));
        PointLight_SetEmissivityRange(fillLight, 35.0f);
    }
    float currentTime = Game_GetTime();
    float deltaTime = Game_GetTick();
    if (!gameOver && !levelComplete) {
        for (int i = 0; i < 150; i++) {
            if (enemySpeeds[i] > 0.0f) {
                if (enemyCanJump[i]) {
                    if (Collision_Check(playerBase, enemyEllipsoids[i], 100) || Collision_Check(playerCannon, enemyEllipsoids[i], 100)) {
                        gameOver = true;
                        Primitive_SetInvisible(gameOverText, false);
                        Primitive_SetInvisible(playAgainButton, false);
                        if (score > bestScore) {
                            bestScore = score;
                            Primitive_SetTextNumber(bestScoreText, 0, (float)bestScore);
                        }
                        break;
                    }
                } else if (enemySpeeds[i] > 2.0f) {
                    if (Collision_Check(playerBase, enemyCylinders[i], 100) || Collision_Check(playerCannon, enemyCylinders[i], 100)) {
                        gameOver = true;
                        Primitive_SetInvisible(gameOverText, false);
                        Primitive_SetInvisible(playAgainButton, false);
                        if (score > bestScore) {
                            bestScore = score;
                            Primitive_SetTextNumber(bestScoreText, 0, (float)bestScore);
                        }
                        break;
                    }
                } else {
                    if (Collision_Check(playerBase, enemyBoxes[i], 100) || Collision_Check(playerCannon, enemyBoxes[i], 100)) {
                        gameOver = true;
                        Primitive_SetInvisible(gameOverText, false);
                        Primitive_SetInvisible(playAgainButton, false);
                        if (score > bestScore) {
                            bestScore = score;
                            Primitive_SetTextNumber(bestScoreText, 0, (float)bestScore);
                        }
                        break;
                    }
                }
            }
        }
        bool allEnemiesGone = true;
        for (int i = 0; i < 150; i++) {
            if (enemySpeeds[i] > 0.0f) {
                Vector3 pos;
                if (enemyCanJump[i]) {
                    pos = Primitive_GetLocation(enemyEllipsoids[i]);
                } else if (enemySpeeds[i] > 2.0f) {
                    pos = Primitive_GetLocation(enemyCylinders[i]);
                } else {
                    pos = Primitive_GetLocation(enemyBoxes[i]);
                }
                if (pos.z <= 0.0f) {
                    allEnemiesGone = false;
                } else {
                    if (enemyCanJump[i]) {
                        Primitive_SetInvisible(enemyEllipsoids[i], true);
                    } else if (enemySpeeds[i] > 2.0f) {
                        Primitive_SetInvisible(enemyCylinders[i], true);
                    } else {
                        Primitive_SetInvisible(enemyBoxes[i], true);
                    }
                    enemySpeeds[i] = 0.0f;
                }
            }
        }
        if (allEnemiesGone) {
            levelComplete = true;
            Primitive_SetInvisible(playerBase, true);
            Primitive_SetInvisible(playerCannon, true);
            Primitive_SetInvisible(levelCompleteText, false);
            Primitive_SetInvisible(continueButton, false);
            if (score > bestScore) {
                bestScore = score;
                Primitive_SetTextNumber(bestScoreText, 0, (float)bestScore);
            }
        }
    }
    if (!gameOver && !levelComplete && Mouse_Down()) {
        if (!isDragging) {
            isDragging = true;
            dragStartX = Mouse_X();
            boxStartX = boxXPosition;
        }
        if (isDragging) {
            float mouseX = Mouse_X();
            boxXPosition = boxStartX + ((mouseX - dragStartX) * 2.5f);
            if (boxXPosition < -1.2f) {
                boxXPosition = -1.2f;
            }
            if (boxXPosition > 1.2f) {
                boxXPosition = 1.2f;
            }
            Primitive_SetLocation(playerBase, Vector3_Create(boxXPosition, 0.0f, 0.0f));
            Primitive_SetLocation(playerCannon, Vector3_Create(boxXPosition, 0.05f, -0.05f));
        }
        if ((currentTime - lastShotTime) >= 0.08f) {
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
    if ((gameOver || levelComplete) && Mouse_Click()) {
        int clicked = Clicked_GetPrimitive();
        if (Primitive_IsText(clicked)) {
            if (clicked == playAgainButton && gameOver) {
                ResetGame();
            } else if (clicked == continueButton && levelComplete) {
                ResetGame();
            }
        }
    }
    if (!gameOver && !levelComplete) {
        for (int i = 0; i < 50; i++) {
            if (bulletSpeeds[i] > 0.0f) {
                UpdateBullet(i, deltaTime, currentTime);
            }
        }
        for (int i = 0; i < 150; i++) {
            if (enemySpeeds[i] > 0.0f) {
                UpdateEnemy(i, deltaTime);
            }
        }
        UpdateBonus(deltaTime);
    }
    for (int i = 0; i < 5; i++) {
        if (labelVisible[i]) {
            if (currentTime - labelTimes[i] > 1.0f) {
                Primitive_SetInvisible(scoreLabels[i], true);
                labelVisible[i] = false;
            } else {
                Vector3 screenPos = View_Project3DLocationToScreen(labelPositions[i]);
                if (screenPos.z > 0.0f) {
                    Primitive_SetTextNumber(scoreLabels[i], 0, labelScores[i]);
                    Primitive_SetLocation(scoreLabels[i], Vector3_Create(screenPos.x, screenPos.y, 0.0f));
                    Primitive_SetInvisible(scoreLabels[i], false);
                } else {
                    Primitive_SetInvisible(scoreLabels[i], true);
                }
            }
        }
    }
}