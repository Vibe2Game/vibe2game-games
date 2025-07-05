Cylinder mainBody;
Box cockpit;
Box leftWing;
Box rightWing;
Box topFin;
Box bottomFin;
Sphere frontLight;
Sphere leftEngine;
Sphere rightEngine;
Cylinder exhaust;
Box leftCargo;
Box rightCargo;
Cylinder antenna;
Sphere leftWindow1;
Sphere leftWindow2;
Sphere leftWindow3;
Sphere rightWindow1;
Sphere rightWindow2;
Sphere rightWindow3;
Sphere sun;
Sphere mercury;
Sphere venus;
Sphere earth;
Sphere mars;
Sphere jupiter;
Sphere saturn;
Sphere uranus;
Sphere neptune;
Sphere pluto;
Material mainBodyMaterial;
Material cockpitMaterial;
Material wingMaterial;
Material finMaterial;
Material lightMaterial;
Material engineMaterial;
Material exhaustMaterial;
Material cargoMaterial;
Material antennaMaterial;
Material windowMaterial;
Material sunMaterial;
Material mercuryMaterial;
Material venusMaterial;
Material earthMaterial;
Material marsMaterial;
Material jupiterMaterial;
Material saturnMaterial;
Material uranusMaterial;
Material neptuneMaterial;
Material plutoMaterial;
Vector3 mainBodyOffset;
Vector3 cockpitOffset;
Vector3 leftWingOffset;
Vector3 rightWingOffset;
Vector3 topFinOffset;
Vector3 bottomFinOffset;
Vector3 frontLightOffset;
Vector3 leftEngineOffset;
Vector3 rightEngineOffset;
Vector3 exhaustOffset;
Vector3 leftCargoOffset;
Vector3 rightCargoOffset;
Vector3 antennaOffset;
Vector3 leftWindow1Offset;
Vector3 leftWindow2Offset;
Vector3 leftWindow3Offset;
Vector3 rightWindow1Offset;
Vector3 rightWindow2Offset;
Vector3 rightWindow3Offset;
Vector3 center;
Vector3 spaceshipPosition;
Vector3 spaceshipVelocity;
Vector3 targetPosition;
bool isMoving;
float maxSpeed;
float acceleration;
bool isDragging;
float dragStartX;
float dragStartAzimuth;
PointLight sunLight;
int planetLabels[9];
Vector3 planetPositions[9];
Quaternion spaceshipOrientation;
float planetRadii[9];
Quaternion targetOrientation;
Vector3 currentLookAt;
float prices[144];
float base_prices[16];
float distances[81];
int targetPlanet;
int goodsTexts[16];
int planetNameTexts[9];
int inventory[16];
float balance;
int inventoryTexts[16];
int balanceText;
Sphere stars[500];
Material starMaterials[500];

void Game_Update() {
   if (Game_IsInitializing()) {
      mainBody = Primitive_CreateCylinder();
      cockpit = Primitive_CreateBox();
      leftWing = Primitive_CreateBox();
      rightWing = Primitive_CreateBox();
      topFin = Primitive_CreateBox();
      bottomFin = Primitive_CreateBox();
      frontLight = Primitive_CreateSphere();
      leftEngine = Primitive_CreateSphere();
      rightEngine = Primitive_CreateSphere();
      exhaust = Primitive_CreateCylinder();
      leftCargo = Primitive_CreateBox();
      rightCargo = Primitive_CreateBox();
      antenna = Primitive_CreateCylinder();
      leftWindow1 = Primitive_CreateSphere();
      leftWindow2 = Primitive_CreateSphere();
      leftWindow3 = Primitive_CreateSphere();
      rightWindow1 = Primitive_CreateSphere();
      rightWindow2 = Primitive_CreateSphere();
      rightWindow3 = Primitive_CreateSphere();
      sun = Primitive_CreateSphere();
      mercury = Primitive_CreateSphere();
      venus = Primitive_CreateSphere();
      earth = Primitive_CreateSphere();
      mars = Primitive_CreateSphere();
      jupiter = Primitive_CreateSphere();
      saturn = Primitive_CreateSphere();
      uranus = Primitive_CreateSphere();
      neptune = Primitive_CreateSphere();
      pluto = Primitive_CreateSphere();
      mainBodyMaterial = Material_Create();
      cockpitMaterial = Material_Create();
      wingMaterial = Material_Create();
      finMaterial = Material_Create();
      lightMaterial = Material_Create();
      engineMaterial = Material_Create();
      exhaustMaterial = Material_Create();
      cargoMaterial = Material_Create();
      antennaMaterial = Material_Create();
      windowMaterial = Material_Create();
      sunMaterial = Material_Create();
      mercuryMaterial = Material_Create();
      venusMaterial = Material_Create();
      earthMaterial = Material_Create();
      marsMaterial = Material_Create();
      jupiterMaterial = Material_Create();
      saturnMaterial = Material_Create();
      uranusMaterial = Material_Create();
      neptuneMaterial = Material_Create();
      plutoMaterial = Material_Create();
      for(int i=0; i<500; i=i+1) {
         stars[i] = Primitive_CreateSphere();
         starMaterials[i] = Material_Create();
      }
      Material_SetColor(mainBodyMaterial, Color_Create(0.3f, 0.3f, 0.3f, 1.0f));
      Material_SetGlossiness(mainBodyMaterial, 0.25f);
      Material_SetColor(cockpitMaterial, Color_Create(0.2f, 0.2f, 0.3f, 1.0f));
      Material_SetGlossiness(cockpitMaterial, 0.5f);
      Material_SetColor(wingMaterial, Color_Create(0.25f, 0.25f, 0.25f, 1.0f));
      Material_SetGlossiness(wingMaterial, 0.25f);
      Material_SetColor(finMaterial, Color_Create(0.2f, 0.2f, 0.25f, 1.0f));
      Material_SetGlossiness(finMaterial, 0.25f);
      Material_SetColor(lightMaterial, Color_Create(1.0f, 0.8f, 0.6f, 1.0f));
      Material_SetGlossiness(lightMaterial, -1.0f);
      Material_SetColor(engineMaterial, Color_Create(0.4f, 0.4f, 0.4f, 1.0f));
      Material_SetGlossiness(engineMaterial, 0.5f);
      Material_SetColor(exhaustMaterial, Color_Create(0.5f, 0.5f, 0.5f, 1.0f));
      Material_SetGlossiness(exhaustMaterial, 0.1f);
      Material_SetColor(cargoMaterial, Color_Create(0.35f, 0.35f, 0.35f, 1.0f));
      Material_SetGlossiness(cargoMaterial, 0.1f);
      Material_SetColor(antennaMaterial, Color_Create(0.2f, 0.2f, 0.2f, 1.0f));
      Material_SetGlossiness(antennaMaterial, 0.5f);
      Material_SetColor(windowMaterial, Color_Create(0.8f, 0.9f, 1.0f, 1.0f));
      Material_SetGlossiness(windowMaterial, -1.0f);
      Material_SetColor(sunMaterial, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Material_SetGlossiness(sunMaterial, -1.0f);
      Material_SetColor(mercuryMaterial, Color_Create(0.5f, 0.5f, 0.5f, 1.0f));
      Material_SetGlossiness(mercuryMaterial, 0.0f);
      Material_SetColor(venusMaterial, Color_Create(1.0f, 0.9f, 0.5f, 1.0f));
      Material_SetGlossiness(venusMaterial, 0.0f);
      Material_SetColor(earthMaterial, Color_Create(0.0f, 0.5f, 1.0f, 1.0f));
      Material_SetGlossiness(earthMaterial, 0.0f);
      Material_SetColor(marsMaterial, Color_Create(1.0f, 0.3f, 0.0f, 1.0f));
      Material_SetGlossiness(marsMaterial, 0.0f);
      Material_SetColor(jupiterMaterial, Color_Create(1.0f, 0.6f, 0.0f, 1.0f));
      Material_SetGlossiness(jupiterMaterial, 0.0f);
      Material_SetColor(saturnMaterial, Color_Create(1.0f, 0.8f, 0.5f, 1.0f));
      Material_SetGlossiness(saturnMaterial, 0.0f);
      Material_SetColor(uranusMaterial, Color_Create(0.5f, 0.8f, 1.0f, 1.0f));
      Material_SetGlossiness(uranusMaterial, 0.0f);
      Material_SetColor(neptuneMaterial, Color_Create(0.0f, 0.0f, 1.0f, 1.0f));
      Material_SetGlossiness(neptuneMaterial, 0.0f);
      Material_SetColor(plutoMaterial, Color_Create(0.8f, 0.8f, 0.8f, 1.0f));
      Material_SetGlossiness(plutoMaterial, 0.0f);
      for(int i=0; i<500; i=i+1) {
         float colorType = Float_RandomizeDeterministic(0.0f, 1.0f);
         Color starColor;
         if(colorType < 0.33f) {
            starColor = Color_Create(0.7f, 0.7f, 1.0f, 1.0f);
         } else if(colorType < 0.66f) {
            starColor = Color_Create(1.0f, 1.0f, 1.0f, 1.0f);
         } else {
            starColor = Color_Create(1.0f, 0.8f, 0.5f, 1.0f);
         }
         Material_SetColor(starMaterials[i], starColor);
         Material_SetGlossiness(starMaterials[i], -1.0f);
         Primitive_SetSphereRadius(stars[i], 0.1f);
         Primitive_SetMaterial(stars[i], starMaterials[i]);
         float u = Float_RandomizeDeterministic(-1.0f, 1.0f);
         float v = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
         float phi = Float_ASin(u);
         float theta = v;
         float r = 110000.0f;
         float x = r * Float_Cos(phi) * Float_Cos(theta);
         float y = r * Float_Sin(phi);
         float z = r * Float_Cos(phi) * Float_Sin(theta);
         Vector3 starPos = Vector3_Create(x, y, z);
         Primitive_SetLocation(stars[i], starPos);
      }
      center = Vector3_Create(0.0f, 0.0f, -0.2f);
      mainBodyOffset = Vector3_Create(0.0f, 0.0f, -0.2f) - center;
      Primitive_SetCylinderLength(mainBody, 1.5f);
      Primitive_SetCylinderRadii(mainBody, 0.3f, 0.2f);
      Primitive_SetMaterial(mainBody, mainBodyMaterial);
      Primitive_SetLocation(mainBody, Vector3_Create(0.0f, 0.0f, -0.2f));
      cockpitOffset = Vector3_Create(0.0f, 0.0f, 0.5f) - center;
      Primitive_SetBoxDimensions(cockpit, Vector3_Create(0.4f, 0.3f, 0.4f));
      Primitive_SetBoxCornerRadius(cockpit, 0.1f);
      Primitive_SetMaterial(cockpit, cockpitMaterial);
      Primitive_SetLocation(cockpit, Vector3_Create(0.0f, 0.0f, 0.5f));
      leftWingOffset = Vector3_Create(-0.5f, 0.0f, -0.2f) - center;
      Primitive_SetBoxDimensions(leftWing, Vector3_Create(0.6f, 0.08f, 0.3f));
      Primitive_SetBoxFrontShrinking(leftWing, 0.5f);
      Primitive_SetBoxCornerRadius(leftWing, 0.05f);
      Primitive_SetMaterial(leftWing, wingMaterial);
      Primitive_SetLocation(leftWing, Vector3_Create(-0.5f, 0.0f, -0.2f));
      rightWingOffset = Vector3_Create(0.5f, 0.0f, -0.2f) - center;
      Primitive_SetBoxDimensions(rightWing, Vector3_Create(0.6f, 0.08f, 0.3f));
      Primitive_SetBoxFrontShrinking(rightWing, 0.5f);
      Primitive_SetBoxCornerRadius(rightWing, 0.05f);
      Primitive_SetMaterial(rightWing, wingMaterial);
      Primitive_SetLocation(rightWing, Vector3_Create(0.5f, 0.0f, -0.2f));
      topFinOffset = Vector3_Create(0.0f, 0.45f, -0.2f) - center;
      Primitive_SetBoxDimensions(topFin, Vector3_Create(0.2f, 0.5f, 0.3f));
      Primitive_SetBoxFrontShrinking(topFin, 0.3f);
      Primitive_SetMaterial(topFin, finMaterial);
      Primitive_SetLocation(topFin, Vector3_Create(0.0f, 0.45f, -0.2f));
      bottomFinOffset = Vector3_Create(0.0f, -0.45f, -0.2f) - center;
      Primitive_SetBoxDimensions(bottomFin, Vector3_Create(0.2f, 0.5f, 0.3f));
      Primitive_SetBoxFrontShrinking(bottomFin, 0.3f);
      Primitive_SetMaterial(bottomFin, finMaterial);
      Primitive_SetLocation(bottomFin, Vector3_Create(0.0f, -0.45f, -0.2f));
      frontLightOffset = Vector3_Create(0.0f, 0.0f, 0.6f) - center;
      Primitive_SetSphereRadius(frontLight, 0.15f);
      Primitive_SetMaterial(frontLight, lightMaterial);
      Primitive_SetLocation(frontLight, Vector3_Create(0.0f, 0.0f, 0.6f));
      leftEngineOffset = Vector3_Create(-0.3f, 0.0f, -0.8f) - center;
      Primitive_SetSphereRadius(leftEngine, 0.15f);
      Primitive_SetMaterial(leftEngine, engineMaterial);
      Primitive_SetLocation(leftEngine, Vector3_Create(-0.3f, 0.0f, -0.8f));
      rightEngineOffset = Vector3_Create(0.3f, 0.0f, -0.8f) - center;
      Primitive_SetSphereRadius(rightEngine, 0.15f);
      Primitive_SetMaterial(rightEngine, engineMaterial);
      Primitive_SetLocation(rightEngine, Vector3_Create(0.3f, 0.0f, -0.8f));
      exhaustOffset = Vector3_Create(0.0f, 0.0f, -0.95f) - center;
      Primitive_SetCylinderLength(exhaust, 0.3f);
      Primitive_SetCylinderRadii(exhaust, 0.1f, 0.1f);
      Primitive_SetMaterial(exhaust, exhaustMaterial);
      Primitive_SetLocation(exhaust, Vector3_Create(0.0f, 0.0f, -0.95f));
      leftCargoOffset = Vector3_Create(-0.35f, 0.0f, -0.4f) - center;
      Primitive_SetBoxDimensions(leftCargo, Vector3_Create(0.2f, 0.2f, 0.4f));
      Primitive_SetBoxCornerRadius(leftCargo, 0.05f);
      Primitive_SetMaterial(leftCargo, cargoMaterial);
      Primitive_SetLocation(leftCargo, Vector3_Create(-0.35f, 0.0f, -0.4f));
      rightCargoOffset = Vector3_Create(0.35f, 0.0f, -0.4f) - center;
      Primitive_SetBoxDimensions(rightCargo, Vector3_Create(0.2f, 0.2f, 0.4f));
      Primitive_SetBoxCornerRadius(rightCargo, 0.05f);
      Primitive_SetMaterial(rightCargo, cargoMaterial);
      Primitive_SetLocation(rightCargo, Vector3_Create(0.35f, 0.0f, -0.4f));
      antennaOffset = Vector3_Create(0.0f, 0.3f, 0.0f) - center;
      Primitive_SetCylinderLength(antenna, 0.2f);
      Primitive_SetCylinderRadii(antenna, 0.02f, 0.02f);
      Primitive_SetMaterial(antenna, antennaMaterial);
      Primitive_SetLocation(antenna, Vector3_Create(0.0f, 0.3f, 0.0f));
      leftWindow1Offset = Vector3_Create(-0.3f, 0.0f, 0.0f) - center;
      Primitive_SetSphereRadius(leftWindow1, 0.08f);
      Primitive_SetMaterial(leftWindow1, windowMaterial);
      Primitive_SetLocation(leftWindow1, Vector3_Create(-0.3f, 0.0f, 0.0f));
      leftWindow2Offset = Vector3_Create(-0.3f, 0.0f, -0.2f) - center;
      Primitive_SetSphereRadius(leftWindow2, 0.08f);
      Primitive_SetMaterial(leftWindow2, windowMaterial);
      Primitive_SetLocation(leftWindow2, Vector3_Create(-0.3f, 0.0f, -0.2f));
      leftWindow3Offset = Vector3_Create(-0.3f, 0.0f, -0.4f) - center;
      Primitive_SetSphereRadius(leftWindow3, 0.08f);
      Primitive_SetMaterial(leftWindow3, windowMaterial);
      Primitive_SetLocation(leftWindow3, Vector3_Create(-0.3f, 0.0f, -0.4f));
      rightWindow1Offset = Vector3_Create(0.3f, 0.0f, 0.0f) - center;
      Primitive_SetSphereRadius(rightWindow1, 0.08f);
      Primitive_SetMaterial(rightWindow1, windowMaterial);
      Primitive_SetLocation(rightWindow1, Vector3_Create(0.3f, 0.0f, 0.0f));
      rightWindow2Offset = Vector3_Create(0.3f, 0.0f, -0.2f) - center;
      Primitive_SetSphereRadius(rightWindow2, 0.08f);
      Primitive_SetMaterial(rightWindow2, windowMaterial);
      Primitive_SetLocation(rightWindow2, Vector3_Create(0.3f, 0.0f, -0.2f));
      rightWindow3Offset = Vector3_Create(0.3f, 0.0f, -0.4f) - center;
      Primitive_SetSphereRadius(rightWindow3, 0.08f);
      Primitive_SetMaterial(rightWindow3, windowMaterial);
      Primitive_SetLocation(rightWindow3, Vector3_Create(0.3f, 0.0f, -0.4f));
      Primitive_SetSphereRadius(sun, 349.76f);
      Primitive_SetMaterial(sun, sunMaterial);
      Primitive_SetSphereRadius(mercury, 6.13f);
      Primitive_SetMaterial(mercury, mercuryMaterial);
      Primitive_SetSphereRadius(venus, 15.2f);
      Primitive_SetMaterial(venus, venusMaterial);
      Primitive_SetSphereRadius(earth, 16.0f);
      Primitive_SetMaterial(earth, earthMaterial);
      Primitive_SetSphereRadius(mars, 8.51f);
      Primitive_SetMaterial(mars, marsMaterial);
      Primitive_SetSphereRadius(jupiter, 175.52f);
      Primitive_SetMaterial(jupiter, jupiterMaterial);
      Primitive_SetSphereRadius(saturn, 146.24f);
      Primitive_SetMaterial(saturn, saturnMaterial);
      Primitive_SetSphereRadius(uranus, 64.16f);
      Primitive_SetMaterial(uranus, uranusMaterial);
      Primitive_SetSphereRadius(neptune, 62.24f);
      Primitive_SetMaterial(neptune, neptuneMaterial);
      Primitive_SetSphereRadius(pluto, 3.0f);
      Primitive_SetMaterial(pluto, plutoMaterial);
      Primitive_SetLocation(sun, Vector3_Create(0.0f, 0.0f, 0.0f));
      Randomizer_SetDeterministicSeed(1234);
      float thetaMercury = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yMercury = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 mercuryPos = Vector3_Create(1170.0f * Float_Cos(thetaMercury), yMercury, 1170.0f * Float_Sin(thetaMercury));
      Primitive_SetLocation(mercury, mercuryPos);
      planetPositions[0] = mercuryPos;
      float thetaVenus = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yVenus = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 venusPos = Vector3_Create(2160.0f * Float_Cos(thetaVenus), yVenus, 2160.0f * Float_Sin(thetaVenus));
      Primitive_SetLocation(venus, venusPos);
      planetPositions[1] = venusPos;
      float thetaEarth = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yEarth = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 earthPos = Vector3_Create(3000.0f * Float_Cos(thetaEarth), yEarth, 3000.0f * Float_Sin(thetaEarth));
      Primitive_SetLocation(earth, earthPos);
      planetPositions[2] = earthPos;
      float thetaMars = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yMars = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 marsPos = Vector3_Create(4560.0f * Float_Cos(thetaMars), yMars, 4560.0f * Float_Sin(thetaMars));
      Primitive_SetLocation(mars, marsPos);
      planetPositions[3] = marsPos;
      float thetaJupiter = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yJupiter = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 jupiterPos = Vector3_Create(15600.0f * Float_Cos(thetaJupiter), yJupiter, 15600.0f * Float_Sin(thetaJupiter));
      Primitive_SetLocation(jupiter, jupiterPos);
      planetPositions[4] = jupiterPos;
      float thetaSaturn = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float ySaturn = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 saturnPos = Vector3_Create(28740.0f * Float_Cos(thetaSaturn), ySaturn, 28740.0f * Float_Sin(thetaSaturn));
      Primitive_SetLocation(saturn, saturnPos);
      planetPositions[5] = saturnPos;
      float thetaUranus = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yUranus = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 uranusPos = Vector3_Create(57600.0f * Float_Cos(thetaUranus), yUranus, 57600.0f * Float_Sin(thetaUranus));
      Primitive_SetLocation(uranus, uranusPos);
      planetPositions[6] = uranusPos;
      float thetaNeptune = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yNeptune = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 neptunePos = Vector3_Create(90180.0f * Float_Cos(thetaNeptune), yNeptune, 90180.0f * Float_Sin(thetaNeptune));
      Primitive_SetLocation(neptune, neptunePos);
      planetPositions[7] = neptunePos;
      float thetaPluto = Float_RandomizeDeterministic(0.0f, 2.0f * PI);
      float yPluto = Float_RandomizeDeterministic(-2500.0f, 2500.0f);
      Vector3 plutoPos = Vector3_Create(100000.0f * Float_Cos(thetaPluto), yPluto, 100000.0f * Float_Sin(thetaPluto));
      Primitive_SetLocation(pluto, plutoPos);
      planetPositions[8] = plutoPos;
      planetLabels[0] = Primitive_CreateText("Mercury - (#0.0)M");
      planetLabels[1] = Primitive_CreateText("Venus - (#0.0)M");
      planetLabels[2] = Primitive_CreateText("Earth - (#0.0)M");
      planetLabels[3] = Primitive_CreateText("Mars - (#0.0)M");
      planetLabels[4] = Primitive_CreateText("Jupiter - (#0.0)M");
      planetLabels[5] = Primitive_CreateText("Saturn - (#0.0)M");
      planetLabels[6] = Primitive_CreateText("Uranus - (#0.0)M");
      planetLabels[7] = Primitive_CreateText("Neptune - (#0.0)M");
      planetLabels[8] = Primitive_CreateText("Pluto - (#0.0)M");
      for(int i=0; i<9; i=i+1) {
         Primitive_SetTextFont(planetLabels[i], 5);
         Primitive_SetTextSize(planetLabels[i], 0.4f, 0.1f);
         Primitive_SetTextColor(planetLabels[i], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
         Primitive_SetTextBackgroundColor(planetLabels[i], Color_Create(0.0f, 0.0f, 0.0f, 0.0f));
         Primitive_SetTextCornerRadius(planetLabels[i], 0);
         Primitive_SetTextBackdropBlur(planetLabels[i], 0);
      }
      for(int p=0; p<9; p=p+1) {
         for(int q=0; q<9; q=q+1) {
            distances[p*9 + q] = Vector3_Distance(planetPositions[p], planetPositions[q]);
         }
      }
      for(int k=0; k<16; k=k+1) {
         base_prices[k] = 50.0f + Float_RandomizeDeterministic(0.0f, 100.0f);
      }
      for(int p=0; p<9; p=p+1) {
         for(int k=0; k<16; k=k+1) {
            int production_center = k / 2;
            if (p == production_center) {
               prices[p*16 + k] = base_prices[k];
            } else {
               float price = base_prices[k] + (0.005f * distances[production_center*9 + p]);
               if (Float_RandomizeDeterministic(0.0f, 1.0f) < 0.2f) {
                  prices[p*16 + k] = 0.0f;
               } else {
                  prices[p*16 + k] = price;
               }
            }
         }
      }
      goodsTexts[0] = Primitive_CreateText("Fuel.......: $(#0.0)");
      goodsTexts[1] = Primitive_CreateText("Food.......: $(#0.0)");
      goodsTexts[2] = Primitive_CreateText("Water......: $(#0.0)");
      goodsTexts[3] = Primitive_CreateText("Oxygen.....: $(#0.0)");
      goodsTexts[4] = Primitive_CreateText("Metals.....: $(#0.0)");
      goodsTexts[5] = Primitive_CreateText("Electronics: $(#0.0)");
      goodsTexts[6] = Primitive_CreateText("Luxury.....: $(#0.0)");
      goodsTexts[7] = Primitive_CreateText("Medicine...: $(#0.0)");
      goodsTexts[8] = Primitive_CreateText("Tools......: $(#0.0)");
      goodsTexts[9] = Primitive_CreateText("Weapons....: $(#0.0)");
      goodsTexts[10] = Primitive_CreateText("Clothing...: $(#0.0)");
      goodsTexts[11] = Primitive_CreateText("Materials..: $(#0.0)");
      goodsTexts[12] = Primitive_CreateText("Vehicles...: $(#0.0)");
      goodsTexts[13] = Primitive_CreateText("Robots.....: $(#0.0)");
      goodsTexts[14] = Primitive_CreateText("Data.......: $(#0.0)");
      goodsTexts[15] = Primitive_CreateText("Artifacts..: $(#0.0)");
      for(int i=0; i<16; i=i+1) {
         Primitive_SetTextFont(goodsTexts[i], 5);
         Primitive_SetTextSize(goodsTexts[i], 0.4f, 0.1f);
         Primitive_SetTextColor(goodsTexts[i], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
         Primitive_SetTextBackgroundColor(goodsTexts[i], Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
         Primitive_SetTextCornerRadius(goodsTexts[i], 10);
         Primitive_SetTextBackdropBlur(goodsTexts[i], 8);
         Primitive_SetLocation(goodsTexts[i], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
      for(int i=0; i<9; i=i+1) {
         if(i==0) planetNameTexts[i] = Primitive_CreateText("Orbiting: Mercury");
         if(i==1) planetNameTexts[i] = Primitive_CreateText("Orbiting: Venus");
         if(i==2) planetNameTexts[i] = Primitive_CreateText("Orbiting: Earth");
         if(i==3) planetNameTexts[i] = Primitive_CreateText("Orbiting: Mars");
         if(i==4) planetNameTexts[i] = Primitive_CreateText("Orbiting: Jupiter");
         if(i==5) planetNameTexts[i] = Primitive_CreateText("Orbiting: Saturn");
         if(i==6) planetNameTexts[i] = Primitive_CreateText("Orbiting: Uranus");
         if(i==7) planetNameTexts[i] = Primitive_CreateText("Orbiting: Neptune");
         if(i==8) planetNameTexts[i] = Primitive_CreateText("Orbiting: Pluto");
         Primitive_SetTextFont(planetNameTexts[i], 5);
         Primitive_SetTextSize(planetNameTexts[i], 0.5f, 0.1f);
         Primitive_SetTextColor(planetNameTexts[i], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
         Primitive_SetTextBackgroundColor(planetNameTexts[i], Color_Create(0.0f, 0.0f, 0.0f, 0.0f));
         Primitive_SetTextCornerRadius(planetNameTexts[i], 0);
         Primitive_SetTextBackdropBlur(planetNameTexts[i], 0);
         Primitive_SetLocation(planetNameTexts[i], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
      for(int k=0; k<16; k=k+1) {
         inventory[k] = 0;
      }
      balance = 1000.0f;
      inventoryTexts[0] = Primitive_CreateText("Fuel.......: (#0.0)");
      inventoryTexts[1] = Primitive_CreateText("Food.......: (#0.0)");
      inventoryTexts[2] = Primitive_CreateText("Water......: (#0.0)");
      inventoryTexts[3] = Primitive_CreateText("Oxygen.....: (#0.0)");
      inventoryTexts[4] = Primitive_CreateText("Metals.....: (#0.0)");
      inventoryTexts[5] = Primitive_CreateText("Electronics: (#0.0)");
      inventoryTexts[6] = Primitive_CreateText("Luxury.....: (#0.0)");
      inventoryTexts[7] = Primitive_CreateText("Medicine...: (#0.0)");
      inventoryTexts[8] = Primitive_CreateText("Tools......: (#0.0)");
      inventoryTexts[9] = Primitive_CreateText("Weapons....: (#0.0)");
      inventoryTexts[10] = Primitive_CreateText("Clothing...: (#0.0)");
      inventoryTexts[11] = Primitive_CreateText("Materials..: (#0.0)");
      inventoryTexts[12] = Primitive_CreateText("Vehicles...: (#0.0)");
      inventoryTexts[13] = Primitive_CreateText("Robots.....: (#0.0)");
      inventoryTexts[14] = Primitive_CreateText("Data.......: (#0.0)");
      inventoryTexts[15] = Primitive_CreateText("Artifacts..: (#0.0)");
      for(int i=0; i<16; i=i+1) {
         Primitive_SetTextFont(inventoryTexts[i], 5);
         Primitive_SetTextSize(inventoryTexts[i], 0.4f, 0.1f);
         Primitive_SetTextColor(inventoryTexts[i], Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
         Primitive_SetTextBackgroundColor(inventoryTexts[i], Color_Create(0.0f, 0.0f, 0.0f, 0.5f));
         Primitive_SetTextCornerRadius(inventoryTexts[i], 10);
         Primitive_SetTextBackdropBlur(inventoryTexts[i], 8);
         Primitive_SetLocation(inventoryTexts[i], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
      balanceText = Primitive_CreateText("Balance: $(#0.0)");
      Primitive_SetTextFont(balanceText, 5);
      Primitive_SetTextSize(balanceText, 0.5f, 0.1f);
      Primitive_SetTextColor(balanceText, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      Primitive_SetTextBackgroundColor(balanceText, Color_Create(0.0f, 0.0f, 0.0f, 0.0f));
      Primitive_SetTextCornerRadius(balanceText, 0);
      Primitive_SetTextBackdropBlur(balanceText, 0);
      Primitive_SetLocation(balanceText, Vector3_Create(0.0f, 0.0f, -1.0f));
      spaceshipPosition = Vector3_Create(earthPos.x + 25.0f, earthPos.y, earthPos.z);
      spaceshipVelocity = Vector3_Create(0.0f, 0.0f, 0.0f);
      isMoving = false;
      maxSpeed = 18036.0f / 20.0f;
      acceleration = 18036.0f;
      isDragging = false;
      dragStartX = 0.0f;
      dragStartAzimuth = 0.0f;
      View_SetMode(2);
      View_InitOrbit(30.0f, 0.0f, 5.0f);
      View_SetFieldOfViewAngle(60.0f);
      View_SetZoomSensitivity(5.0f);
      View_SetClipPlanes(0.1f, 120000.0f);
      AmbientLight_Set(Color_Create(0.01f, 0.01f, 0.1f, 1.0f));
      Environment_SetGradient(Color_Create(0.10f, 0.10f, 0.10f, 1.0f), Color_Create(0.025f, 0.025f, 0.025f, 1.0f), Color_Create(0.01f, 0.01f, 0.01f, 1.0f), Color_Create(0.0f, 0.0f, 0.0f, 1.0f), 0.33f, 0.66f);
      sunLight = PointLight_Create(0.0f);
      PointLight_SetLocation(sunLight, Vector3_Create(0.0f, 0.0f, 0.0f));
      PointLight_SetColor(sunLight, Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
      PointLight_SetEmissivityRange(sunLight, 120000.0f);
      spaceshipOrientation = Quaternion_Create(0.0f, 0.0f, 0.0f, 1.0f);
      targetOrientation = Quaternion_Create(0.0f, 0.0f, 0.0f, 1.0f);
      currentLookAt = spaceshipPosition;
      planetRadii[0] = 6.13f;
      planetRadii[1] = 15.2f;
      planetRadii[2] = 16.0f;
      planetRadii[3] = 8.51f;
      planetRadii[4] = 175.52f;
      planetRadii[5] = 146.24f;
      planetRadii[6] = 64.16f;
      planetRadii[7] = 62.24f;
      planetRadii[8] = 3.0f;
      targetPlanet = 2;
   }
   float deltaTime = Game_GetTick();
   int clickedPrim = Clicked_GetPrimitive();
   if (clickedPrim >= 0) {
      for(int i=0; i<9; i=i+1) {
         if (clickedPrim == planetLabels[i]) {
            Vector3 planetPos = planetPositions[i];
            Vector3 vectorToPlanet = planetPos - spaceshipPosition;
            float distance = Vector3_Length(vectorToPlanet);
            if (distance > 25.0f) {
               Vector3 direction = Vector3_Normalize(vectorToPlanet);
               float planetRadius = planetRadii[i];
               targetPosition = planetPos - (direction * (planetRadius + 25.0f));
               isMoving = true;
               targetPlanet = i;
            }
         }
      }
   }
   if (isMoving) {
      Vector3 direction = Vector3_Normalize(targetPosition - spaceshipPosition);
      float distanceToTarget = Vector3_Distance(spaceshipPosition, targetPosition);
      float speed = Vector3_Length(spaceshipVelocity);
      float stoppingDistance = (speed * speed) / (2.0f * acceleration);
      if (distanceToTarget > stoppingDistance) {
         Vector3 accelerationVector = direction * acceleration;
         spaceshipVelocity = spaceshipVelocity + (accelerationVector * deltaTime);
         if (Vector3_Length(spaceshipVelocity) > maxSpeed) {
            spaceshipVelocity = Vector3_Normalize(spaceshipVelocity) * maxSpeed;
         }
      } else {
         if (speed > 0.0f) {
            Vector3 decelerationVector = -Vector3_Normalize(spaceshipVelocity) * acceleration;
            spaceshipVelocity = spaceshipVelocity + (decelerationVector * deltaTime);
            if (Vector3_Dot(spaceshipVelocity, direction) < 0.0f) {
               spaceshipVelocity = Vector3_Create(0.0f, 0.0f, 0.0f);
            }
         }
      }
      float movementThisFrame = Vector3_Dot(spaceshipVelocity, direction) * deltaTime;
      if (movementThisFrame > distanceToTarget) {
         spaceshipPosition = targetPosition;
         spaceshipVelocity = Vector3_Create(0.0f, 0.0f, 0.0f);
         isMoving = false;
      } else {
         spaceshipPosition = spaceshipPosition + (spaceshipVelocity * deltaTime);
      }
   }
   if (Vector3_Length(spaceshipVelocity) > 0.0001f) {
      Vector3 dir = Vector3_Normalize(spaceshipVelocity);
      targetOrientation = Quaternion_CreateFromDirection(dir);
   }
   spaceshipOrientation = Quaternion_Slerp(spaceshipOrientation, targetOrientation, 5.0f * deltaTime);
   if (isMoving) {
      float t = Game_GetTime();
      float radius = 0.15f + (0.05f * Float_Sin(2.0f * PI * t / 0.25f));
      Primitive_SetSphereRadius(frontLight, radius);
   } else {
      Primitive_SetSphereRadius(frontLight, 0.15f);
   }
   Vector3 rotatedOffset = Vector3_RotateWithQuaternion(mainBodyOffset, spaceshipOrientation);
   Primitive_SetLocation(mainBody, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(mainBody, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(cockpitOffset, spaceshipOrientation);
   Primitive_SetLocation(cockpit, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(cockpit, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(leftWingOffset, spaceshipOrientation);
   Primitive_SetLocation(leftWing, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(leftWing, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(rightWingOffset, spaceshipOrientation);
   Primitive_SetLocation(rightWing, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(rightWing, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(topFinOffset, spaceshipOrientation);
   Primitive_SetLocation(topFin, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(topFin, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(bottomFinOffset, spaceshipOrientation);
   Primitive_SetLocation(bottomFin, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(bottomFin, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(frontLightOffset, spaceshipOrientation);
   Primitive_SetLocation(frontLight, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(frontLight, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(leftEngineOffset, spaceshipOrientation);
   Primitive_SetLocation(leftEngine, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(leftEngine, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(rightEngineOffset, spaceshipOrientation);
   Primitive_SetLocation(rightEngine, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(rightEngine, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(exhaustOffset, spaceshipOrientation);
   Primitive_SetLocation(exhaust, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(exhaust, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(leftCargoOffset, spaceshipOrientation);
   Primitive_SetLocation(leftCargo, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(leftCargo, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(rightCargoOffset, spaceshipOrientation);
   Primitive_SetLocation(rightCargo, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(rightCargo, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(antennaOffset, spaceshipOrientation);
   Primitive_SetLocation(antenna, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(antenna, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(leftWindow1Offset, spaceshipOrientation);
   Primitive_SetLocation(leftWindow1, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(leftWindow1, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(leftWindow2Offset, spaceshipOrientation);
   Primitive_SetLocation(leftWindow2, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(leftWindow2, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(leftWindow3Offset, spaceshipOrientation);
   Primitive_SetLocation(leftWindow3, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(leftWindow3, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(rightWindow1Offset, spaceshipOrientation);
   Primitive_SetLocation(rightWindow1, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(rightWindow1, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(rightWindow2Offset, spaceshipOrientation);
   Primitive_SetLocation(rightWindow2, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(rightWindow2, spaceshipOrientation);
   rotatedOffset = Vector3_RotateWithQuaternion(rightWindow3Offset, spaceshipOrientation);
   Primitive_SetLocation(rightWindow3, spaceshipPosition + rotatedOffset);
   Primitive_SetOrientation(rightWindow3, spaceshipOrientation);
   currentLookAt = Vector3_Interpolate(currentLookAt, spaceshipPosition, 50.0f * deltaTime);
   View_SetLookAtLocation(currentLookAt);
   Vector3 spaceshipPos = Primitive_GetLocation(mainBody);
   for(int i=0; i<9; i=i+1) {
      float distance = Vector3_Distance(spaceshipPos, planetPositions[i]);
      Primitive_SetTextNumber(planetLabels[i], 0, Float_Round(distance));
      Vector3 projected = View_Project3DLocationToScreen(planetPositions[i]);
      if(projected.z > 0.0f) {
         Primitive_SetLocation(planetLabels[i], Vector3_Create(projected.x, projected.y - 0.1f, 0.0f));
      } else {
         Primitive_SetLocation(planetLabels[i], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
   }
   if (!isMoving && (targetPlanet >= 0)) {
      int tradedGoods[16];
      int tradedCount = 0;
      for(int k=0; k<16; k=k+1) {
         if(prices[targetPlanet * 16 + k] > 0.0f) {
            tradedGoods[tradedCount] = k;
            tradedCount = tradedCount + 1;
         }
      }
      for(int k=0; k<16; k=k+1) {
         Primitive_SetLocation(goodsTexts[k], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
      for(int i=0; i<tradedCount; i=i+1) {
         int k = tradedGoods[i];
         float x = -0.75f;
         float y = 0.8f - (0.1f * (float)i);
         Primitive_SetLocation(goodsTexts[k], Vector3_Create(x, y, 0.0f));
         Primitive_SetTextNumber(goodsTexts[k], 0, Float_Round(prices[targetPlanet * 16 + k]));
      }
      for(int k=0; k<16; k=k+1) {
         float x = 0.75f;
         float y = 0.8f - (0.1f * (float)k);
         Primitive_SetLocation(inventoryTexts[k], Vector3_Create(x, y, 0.0f));
         Primitive_SetTextNumber(inventoryTexts[k], 0, (float)inventory[k]);
      }
      Primitive_SetLocation(balanceText, Vector3_Create(0.0f, -0.9f, 0.0f));
      Primitive_SetTextNumber(balanceText, 0, Float_Round(balance));
      for(int i=0; i<9; i=i+1) {
         if (i == targetPlanet) {
            Primitive_SetLocation(planetNameTexts[i], Vector3_Create(0.0f, 0.9f, 0.0f));
         } else {
            Primitive_SetLocation(planetNameTexts[i], Vector3_Create(0.0f, 0.0f, -1.0f));
         }
      }
   } else {
      for(int k=0; k<16; k=k+1) {
         Primitive_SetLocation(goodsTexts[k], Vector3_Create(0.0f, 0.0f, -1.0f));
         Primitive_SetLocation(inventoryTexts[k], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
      Primitive_SetLocation(balanceText, Vector3_Create(0.0f, 0.0f, -1.0f));
      for(int i=0; i<9; i=i+1) {
         Primitive_SetLocation(planetNameTexts[i], Vector3_Create(0.0f, 0.0f, -1.0f));
      }
   }
}