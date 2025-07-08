Spline mySpline;
Sphere mySphere;
Material sphereMaterial;
Sphere pathSpheres[100];
Material pathMaterial;
float sphereSpeed;
float accumulatedTime;
void Game_Update() {
    if (Game_IsInitializing()) {
        int i;
        int numUniquePoints = 16;
        mySpline = Spline_Create(numUniquePoints + 1);
        for (i = 0; i < numUniquePoints + 1; i++) {
            float t = (float)(i % numUniquePoints) / (float)numUniquePoints;
            float angleRadians = t * 2.0f * PI;
            float radiusVar = 50.0f * Float_Sin(4.0f * angleRadians);
            float y = 10.0f * Float_Sin(6.0f * angleRadians);
            float x = (100.0f + radiusVar) * Float_Cos(angleRadians);
            float z = (100.0f + radiusVar) * Float_Sin(angleRadians);
            Vector3 pos = Vector3_Create(x, y, z);
            Spline_SetControlPointLocation(mySpline, i, pos);
        }
        pathMaterial = Material_Create();
        Material_SetColor(pathMaterial, Color_Create(0.0f, 0.0f, 0.0f, 1.0f));
        Material_SetGlossiness(pathMaterial, 0.0f);
        for (i = 0; i < 100; i++) {
            pathSpheres[i] = Primitive_CreateSphere();
            Primitive_SetSphereRadius(pathSpheres[i], 0.1f);
            Primitive_SetMaterial(pathSpheres[i], pathMaterial);
            float splineTime = (float)i / 100.0f;
            Vector3 pos = Spline_GetLocationAtTime(mySpline, splineTime);
            Primitive_SetLocation(pathSpheres[i], pos);
        }
        mySphere = Primitive_CreateSphere();
        Primitive_SetSphereRadius(mySphere, 2.0f);
        Primitive_SetSphereShortening(mySphere, 0.2f);
        Primitive_SetSphereFlattening(mySphere, 0.1f);
        sphereMaterial = Material_Create();
        Material_SetColor(sphereMaterial, Color_Create(1.0f, 0.0f, 0.0f, 1.0f));
        Material_SetGlossiness(sphereMaterial, 0.5f);
        Primitive_SetMaterial(mySphere, sphereMaterial);
        View_SetMode(0);
        View_SetClipPlanes(0.1f, 500.0f);
        View_SetFieldOfViewAngle(60.0f);
        View_SetResponse(0.05f, 0.05f);
        View_SetLockCameraRoll(1);
        AmbientLight_Set(Color_Create(0.1f, 0.1f, 0.1f, 1.0f));
        Environment_SetGradient(Color_Create(0.8f, 0.8f, 0.8f, 1.0f), Color_Create(0.4f, 0.4f, 0.4f, 1.0f), Color_Create(0.2f, 0.2f, 0.2f, 1.0f), Color_Create(0.1f, 0.1f, 0.1f, 1.0f), 0.33f, 0.66f);
        PointLight light1 = PointLight_Create(0.0f);
        PointLight_SetLocation(light1, Vector3_Create(0.0f, 100.0f, 0.0f));
        PointLight_SetColor(light1, Color_Create(0.7f, 0.7f, 0.7f, 1.0f));
        PointLight_SetEmissivityRange(light1, 200.0f);
        PointLight light2 = PointLight_Create(0.0f);
        PointLight_SetLocation(light2, Vector3_Create(0.0f, -100.0f, 0.0f));
        PointLight_SetColor(light2, Color_Create(0.7f, 0.7f, 0.7f, 1.0f));
        PointLight_SetEmissivityRange(light2, 200.0f);
        sphereSpeed = 0.0f;
        accumulatedTime = 0.0f;
    }
    if (Mouse_Down()) {
        sphereSpeed = sphereSpeed + (0.05f * Game_GetTick());
        sphereSpeed = Float_Clamp(sphereSpeed, 0.0f, 0.033f);
    } else {
        sphereSpeed = sphereSpeed - (0.1f * Game_GetTick());
        sphereSpeed = Float_Clamp(sphereSpeed, 0.0f, 0.033f);
    }
    accumulatedTime += sphereSpeed * Game_GetTick();
    float splineTime = Float_Mod(accumulatedTime, 1.0f);
    Vector3 spherePos = Spline_GetLocationAtTime(mySpline, splineTime);
    Quaternion orient = Spline_GetOrientationAtTime(mySpline, splineTime, 0.25f, 0.25f);
    Primitive_SetLocation(mySphere, spherePos);
    Primitive_SetOrientation(mySphere, orient);
    View_SetTargetLocation(spherePos);
    View_SetTargetLocationOffset(Vector3_Create(0.0f, 5.0f, 10.0f));
    View_SetTargetOrientation(orient);
    View_SetLookAtLocation(spherePos);
}