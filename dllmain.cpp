#include <iostream>
#include "includes.h"
#include "menu.h"
#include "FNTool.h"
#include "spoof_call.h"


float rainbowspeed = 0.0005f;
void DrawMenu() {
	ZeroGUI::SetupCanvas(static_canvas);
	ZeroGUI::Input::Handle();




	static Vector2 pos = Vector2(700, 700);
	if (ZeroGUI::Window("ritz's amazing internal [remove = gay caterpillar]", &pos, Vector2{ 500.0f, 400.0f }, ShowMenu))
	{
		//Simple Tabs
		static int tab = 0;
		if (ZeroGUI::ButtonTab("Aimbot", Vector2{ 110, 25 }, tab == 0)) tab = 0;
		if (ZeroGUI::ButtonTab("Esp", Vector2{ 110, 25 }, tab == 1)) tab = 1;
		if (ZeroGUI::ButtonTab("Exploits", Vector2{ 110, 25 }, tab == 2)) tab = 2;
		if (ZeroGUI::ButtonTab("Misc", Vector2{ 110, 25 }, tab == 3)) tab = 3;
		ZeroGUI::NextColumn(130.0f);
		//
		if (tab == 0) {
			//Some Elements

			ZeroGUI::Checkbox("Memory Aim", &Settings::MemoryAim);
			ZeroGUI::Checkbox("Silent Aim", &Settings::SilentAim);
			ZeroGUI::SliderFloat("Fov Size", &FovSize, 30.0f, 700.f);

			//2 lazy to do :shrug:
			//ZeroGUI::PushNextElementY(50.0f);
			//ZeroGUI::Combobox("Target Bone", Vector2{ 100, 25 }, &Settings::BoneTarget, "Head", "Neck", "Chest", "Pelvis", NULL); 
		}
		if (tab == 1) {
			ZeroGUI::Checkbox("Box Esp", &Settings::BoxESP);
			ZeroGUI::Checkbox("Skeleton Esp", &Settings::SkeletonESP);
			ZeroGUI::Checkbox("Line Esp", &Settings::LinesESP);
			ZeroGUI::Checkbox("Name Esp", &Settings::PlayerNameESP);
			ZeroGUI::Checkbox("Distance Esp", &Settings::DistanceESP);
			ZeroGUI::Checkbox("Level Esp", &Settings::LevelESP);
			ZeroGUI::Checkbox("Kills Esp", &Settings::KillsESP);
			ZeroGUI::Checkbox("Platform Esp", &Settings::PlatformESP);
			ZeroGUI::Checkbox("Weapon Esp", &Settings::EnemyWeaponESP);
			ZeroGUI::Checkbox("Ammo Esp", &Settings::AmmoESP);

		}
		if (tab == 2) {
			ZeroGUI::Checkbox("Chams", &Settings::Chams);
			ZeroGUI::Checkbox("SniperTp", &Settings::SniperTp);
			ZeroGUI::Checkbox("InstantReload", &Settings::InstantReload);
			ZeroGUI::Checkbox("RapidFire [4snipers]", &Settings::RapidFire); 
			ZeroGUI::Checkbox("Fov Changer", &Settings::FovChanger);
			ZeroGUI::SliderFloat("Fov Value", &Settings::FovChanger_Value, 0.0f, 180.0f);
		}
		if (tab == 3) {
			ZeroGUI::SliderFloat("Rainbow Speed", &rainbowspeed, 0.0001f, 0.005f);
		}
		
		

		
	}
	ZeroGUI::Draw_Cursor(true);
	ZeroGUI::Render();
}




static BOOL IsNotInScreen(int SizeX, int SizeY, Vector2 Pos) {
	if (((Pos.x <= 0 or Pos.x > SizeX) and (Pos.y <= 0 or Pos.y > SizeY)) or ((Pos.x <= 0 or Pos.x > SizeX) or (Pos.y <= 0 or Pos.y > SizeY))) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

AFortPawn* TargetPawno;
AFortPawn* LocalPawno;
APlayerCameraManager* PlayerCameraManagero;
Vector3 o_CamRot;
Vector3 o_CamLoc;
uintptr_t GlobalPlayerState;
bool initspeed = true;
bool Debuggytest = true;
ue::FString playeraname;
void __forceinline AnsiToWide(char* inAnsi, wchar_t* outWide)
{
	int i = 0;
	for (; inAnsi[i] != '\0'; i++)
		outWide[i] = (wchar_t)(inAnsi)[i];
	outWide[i] = L'\0';
}
#include <cmath>
float color_red;
float color_blue;
float color_green;
float color_speed = -10.0;
static ue::FLinearColor FromHSB(float hue, float saturation, float brightness)
{
	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
		return ue::FLinearColor(
			(float)(brightness),
			(float)(t),
			(float)(p),
			(float)(0.7f)
		);
	}
	else if (h < 2)
	{
		return ue::FLinearColor(
			(float)(q),
			(float)(brightness),
			(float)(p),
			(float)(0.7f)
		);
	}
	else if (h < 3)
	{
		return ue::FLinearColor(
			(float)(p),
			(float)(brightness),
			(float)(t),
			(float)(0.7f)
		);
	}
	else if (h < 4)
	{
		return ue::FLinearColor(
			(float)(p),
			(float)(q),
			(float)(brightness),
			(float)(0.7f)
		);
	}
	else if (h < 5)
	{
		return ue::FLinearColor(
			(float)(t),
			(float)(p),
			(float)(brightness),
			(float)(0.7f)
		);
	}
	else
	{
		return ue::FLinearColor(
			(float)(brightness),
			(float)(p),
			(float)(q),
			(float)(0.7f)
		);
	}
}
ue::FLinearColor GetItemColor(EFortItemTier tier)
{
	if (tier == EFortItemTier::I)
		return ue::FLinearColor(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 0.95f);
	else if (tier == EFortItemTier::II)
		return ue::FLinearColor(58 / 255.0f, 121 / 255.0f, 19 / 255.0f, 0.95f);
	else if (tier == EFortItemTier::III)
		return ue::FLinearColor(18 / 255.0f, 88 / 255.0f, 162 / 255.0f, 0.95f);
	else if (tier == EFortItemTier::IV)
		return ue::FLinearColor(189 / 255.0f, 63 / 255.0f, 250 / 255.0f, 0.95f);
	else if (tier == EFortItemTier::V)
		return ue::FLinearColor(255 / 255.0f, 118 / 255.0f, 5 / 255.0f, 0.95f);
	else if (tier == EFortItemTier::VI)
		return ue::FLinearColor(220 / 255.0f, 160 / 255.0f, 30 / 255.0f, 0.95f);
	else if (tier == EFortItemTier::VII)
		return ue::FLinearColor(0 / 255.0f, 225 / 255.0f, 252 / 255.0f, 0.95f);

	return ue::FLinearColor(123, 123, 123, 0.95f);
}

EFortItemTier GetItemEFortTier(float tier)
{
	int tierI = (int)tier;
	switch (tierI)
	{
	case 1:
		return EFortItemTier::I;
	case 2:
		return EFortItemTier::II;
	case 3:
		return EFortItemTier::III;
	case 4:
		return EFortItemTier::IV;
	case 5:
		return EFortItemTier::V;
	case 6:
		return EFortItemTier::VI;
	case 7:
		return EFortItemTier::VII;
	default:
		return EFortItemTier::I;
	}
}

std::string GetItemTierName(EFortItemTier tier)
{
	switch (tier)
	{
	case EFortItemTier::I:
		return xorstr("Common");
	case EFortItemTier::II:
		return xorstr("Uncommon");
	case EFortItemTier::III:
		return xorstr("Rare");
	case EFortItemTier::IV:
		return xorstr("Epic");
	case EFortItemTier::V:
		return xorstr("Legendary");
	case EFortItemTier::VI:
		return xorstr("Mythic");
	case EFortItemTier::VII:
		return xorstr("Exotic");
	default:
		return xorstr("Common");
	}
}


void DrawFilledRect(UCanvas* pCanvas, Vector2 initial_pos, float width, float height, ue::FLinearColor color)
{
	for (float i = 0.0f; i < height; i += 1.0f)
		pCanvas->K2_DrawLine(Vector2(initial_pos.x, initial_pos.y + i), Vector2(initial_pos.x + width, initial_pos.y + i), 1.0f, color);

}
#define mpe 3.14159265358979323846264338327950288419716939937510582f

void DrawCircle(UCanvas* canvas, int x, int y, int radius, int numsides, ue::FLinearColor color)
{
	float Step = mpe * 2.0 / numsides;
	int Count = 0;
	Vector2 V[128];
	for (float a = 0; a < mpe * 2.0; a += Step)
	{
		float X1 = radius * sdkUssage->STATIC_Cos(a) + x;
		float Y1 = radius * sdkUssage->STATIC_Sin(a) + y;
		float X2 = radius * sdkUssage->STATIC_Cos(a + Step) + x;
		float Y2 = radius * sdkUssage->STATIC_Sin(a + Step) + y;
		V[Count].x = X1;
		V[Count].y = Y1;
		V[Count + 1].x = X2;
		V[Count + 1].y = Y2;
		canvas->K2_DrawLine(Vector2({ V[Count].x, V[Count].y }), Vector2({ X2, Y2 }), 1.5f, color);
	}
}

void DrawTriangle(UCanvas* pCanvas, const Vector2& point1, const Vector2& point2, const Vector2& point3, const ue::FLinearColor& color, bool isFilled)
{
	pCanvas->K2_DrawLine(point1, point2, 1.0f, color);
	pCanvas->K2_DrawLine(point1, point3, 1.0f, color);
	pCanvas->K2_DrawLine(point2, point3, 1.0f, color);
	// Fill it
	if (isFilled) {
		float addX = 0.5f;
		float addY = 1;
		for (float i = point1.y; i < point3.y; i++) {
			// draw line
			pCanvas->K2_DrawLine(Vector2(point1.x + addX, point1.y + addY), Vector2(point2.x - addX, point2.y + addY), 1.0f, color);
			addY++;
			addX += 0.5f;
		}
	}
}
void actorloop() {
	AFortPawn* targetpawn = nullptr;
	float closestTocenter = FLT_MAX;
	width = static_canvas->SizeX();
	height = static_canvas->SizeY();
	auto gworld = ((GWorld*)(*(uintptr_t*)(ue::cached::signatures::GWorld)));
	auto OwningGameInstance = gworld->OwningGameInstance();
	PlayerController = OwningGameInstance->LocalPlayers()->LocalPlayer()->PlayerController();
	auto PlayerCameraManager = PlayerController->PlayerCameraManager();
	auto LocalPawn = (AFortPawn*)PlayerController->LocalPawn();
	auto levels = gworld->Levels();
	
	for (int a = 0; a < levels.Num(); a++) {
		auto level = levels[a];
		if (!level) continue;
		auto actors = levels[a]->ActorArray();
		for (int i = 0; i < actors.Num(); i++) {
			auto actor = actors[i];
			if (!actor || actor == LocalPawn)
				continue;
			if (targetpawn)
			{
				if (actor->IsA(ue::cached::objects::FortProjectileBase) && Settings::SniperTp)
				{
					actor->K2_SetActorLocation(targetpawn->GetBone(98), false, true); //68
					
				}
				
			}
			//int dist = PlayerCameraManager->GetCameraLocation().Distance(actor->RootComponent()->RelativeLocation()) / 100;
			//if (dist <= 15) {
			//	auto name = actor->ObjectName();
			//	static_canvas->K2_DrawText(PlayerCameraManager->ProjectWorldLocationToScreen(width, height, actor->RootComponent()->RelativeLocation()), ue::FLinearColor(0, 1, 0, 1), name, false, true);
			//	//printf("%s", name);
			//	//std::cout << name << "\n";
			//}
			
			if (actor->IsA(ue::cached::objects::actor::FortPlayerPawnAthena)) {

				//GlobalPlayerState = *(uintptr_t*)((uintptr_t)actor + 0x290);
				
					
				
				Vector3 head = actor->GetBone(98);
				//std::cout << head.x << " getbone\n";
				Vector2 head_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, head);
				
				
				//if (Settings::Chams) { actor->ApplyPawnHighlight(ue::FLinearColor(10, 10, 0, 0.5), ue::FLinearColor(10, 10, 0, 0.5)); }
				if (Settings::Chams) {
					static float rainbow;
					rainbow += rainbowspeed;
					if (rainbow > 1.f)
						rainbow = 0.f; actor->ApplyPawnHighlight(FromHSB(rainbow, 1.f, 1.f), FromHSB(rainbow, 1.f, 1.f)); }
			
				if (Settings::FovChanger) { PlayerController->Fov(Settings::FovChanger_Value); }
				if (Settings::RapidFire) { actor->CurrentWeapon()->RapidFire(); }
				
				//int GetAccountLevel();
				

				if (actor != LocalPawn) {

					auto dx = head_w2s.x - (width / 2);
					auto dy = head_w2s.y - (height / 2);
					auto dist = crt::sqrtf(dx * dx + dy * dy);

					if (dist < FovSize && dist < closestTocenter) {
						closestTocenter = dist;
						targetpawn = actor;
					}
					else if (!dist < FovSize && !dist < closestTocenter) {
						TargetPawno = 0;
					}

				}
				TargetPawno = targetpawn;
				LocalPawno = LocalPawn;
				PlayerCameraManagero = PlayerCameraManager;
				
				if (Settings::MemoryAim and targetpawn and PlayerController->IsInputKeyDown(ue::FKey(RBKey))) {
					
					Vector3 headtarget = targetpawn->GetBone(98);
					//std::cout << head.x << " getbone\n";
					Vector2 headtarget_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, headtarget);

					auto camloc = PlayerCameraManager->GetCameraLocation();
					auto NewRotation = galgan(camloc, headtarget);
					PlayerController->ClientSetRotation(NewRotation, false); //never got around to making ud memory none of my attemps to hook get roation shit worked :shrug:

				

				}
				//PlayerController->TurboBuildInterval();
				
				Vector2 head2_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, { head.x, head.y, head.z + 20 });
				//std::cout << head2_w2s.x << " w2s head\n";
				Vector3 bottom = actor->GetBone(0);

				Vector2 bottom_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, { bottom.x, bottom.y, bottom.z });
				//std::cout << bottom_w2s.x << " w2s bottom\n";
				ue::FLinearColor col = ue::FLinearColor(0.f, 1.f, 0.f, 1.f);

				if (IsNotInScreen(width, height, head_w2s)) continue;
				float BoxHeight = (float)(bottom_w2s.y - head2_w2s.y);
				float BoxWidth = BoxHeight * 0.60f;

				float BottomLeftX = (float)head2_w2s.x - BoxWidth / 2;
				float BottomLeftY = (float)bottom_w2s.y;

				float BottomRightX = (float)head2_w2s.x + BoxWidth / 2;
				float BottomRightY = (float)bottom_w2s.y;

				float TopRightX = (float)head2_w2s.x + BoxWidth / 2;
				float TopRightY = (float)head2_w2s.y;

				float TopLeftX = (float)head2_w2s.x - BoxWidth / 2;
				float TopLeftY = (float)head2_w2s.y;

				if (Settings::BoxESP) {
					//Bottom
					static_canvas->K2_DrawLine(Vector2(BottomLeftX, BottomLeftY), Vector2(BottomRightX, BottomRightY), 2.f, col);

					//Right
					static_canvas->K2_DrawLine(Vector2(BottomRightX, BottomRightY), Vector2(TopRightX, TopRightY), 2.f, col);

					//Top
					static_canvas->K2_DrawLine(Vector2(TopRightX, TopRightY), Vector2(TopLeftX, TopLeftY), 2.f, col);

					//Left
					static_canvas->K2_DrawLine(Vector2(TopLeftX, TopLeftY), Vector2(BottomLeftX, BottomLeftY), 2.f, col);
				}
				auto redcol = ue::FLinearColor(1, 0, 0, 1);
				auto bluecol = ue::FLinearColor(0, 0, 1, 1);
				float TextOffset_Y = head2_w2s.y;
				float TextOffset_X = TopRightX + 5;
				Vector2 calculation;
				if (!IsNotInScreen(1920, 1080, head2_w2s)) {
					if (Settings::PlayerNameESP) {
						auto name = actor->PlayerState()->GetPlayerName();
						if (name.c_str()) {

							TextOffset_Y += static_canvas->K2_TextSize(actor->PlayerState()->GetPlayerName()).y + 5;
							calculation = Vector2(TextOffset_X, TextOffset_Y);
							static_canvas->K2_DrawText(calculation, redcol, name.c_str(), false, true);
						}
					}
					if (Settings::DistanceESP) {
						int dist = PlayerCameraManager->GetCameraLocation().Distance(actor->RootComponent()->RelativeLocation()) / 100;
						static char distanceesp[128];
						static wchar_t wdistanceesp[128];
						sprintf(distanceesp, xorstr("Distance: %d[m]"), dist);
						AnsiToWide(distanceesp, wdistanceesp);
						TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wdistanceesp)).y + 10;
						calculation = Vector2(TextOffset_X, TextOffset_Y);
						static_canvas->K2_DrawText(calculation, bluecol, wdistanceesp, false, true);
					}
					if (Settings::LevelESP) {
						auto level = actor->PlayerState()->SeasonLevelUIDisplay();
						static char levelesp[128];
						static wchar_t wlevelesp[128];
						sprintf(levelesp, xorstr("Level: %d"), level);
						AnsiToWide(levelesp, wlevelesp);
						TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wlevelesp)).y + 10;
						calculation = Vector2(TextOffset_X, TextOffset_Y);
						static_canvas->K2_DrawText(calculation, redcol, wlevelesp, false, true);
					}
					if (Settings::KillsESP) {
						auto kills = actor->PlayerState()->GetKillScore();
						static char killesp[128];
						static wchar_t wdkillesp[128];
						sprintf(killesp, xorstr("Kills: %d"), kills);
						AnsiToWide(killesp, wdkillesp);
						TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wdkillesp)).y + 10;
						calculation = Vector2(TextOffset_X, TextOffset_Y);
						static_canvas->K2_DrawText(calculation, bluecol, wdkillesp, false, true);
					}
					if (Settings::PlatformESP) {
						auto platform = actor->PlayerState()->GetPlatform();
						if (!platform.IsValid()) continue;
						auto platform_name = platform.c_str();
						TextOffset_Y += static_canvas->K2_TextSize(ue::FString(platform_name)).y + 10;
						calculation = Vector2(TextOffset_X, TextOffset_Y);

						if (math::custom_wcsstr(platform_name, xorstr(L"PSN"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"PlayStation"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"XBL"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"Xbox"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"XSX"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"Xbox Series S"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"WIN"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"Windows"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"MAC"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"MacOS"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"LNX"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"Linux"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"IOS"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"Ios"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"AND"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"Android"), false, true);
						}
						else if (math::custom_wcsstr(platform_name, xorstr(L"SWT"))) {
							static_canvas->K2_DrawText(calculation, redcol, xorstr(L"NintendoSwitch"), false, true);
						}
						else {
							static_canvas->K2_DrawText(calculation, redcol, platform_name, false, true);
						}
					}
					if (actor->CurrentWeapon()) {
					}
					if (Settings::EnemyWeaponESP) {
						if (actor->CurrentWeapon()->WeaponData()) {
							auto weaponname = actor->CurrentWeapon()->WeaponData()->DisplayName().Get();
							if (weaponname) {
								TextOffset_Y += static_canvas->K2_TextSize(weaponname).y + 10;
								calculation = Vector2(TextOffset_X, TextOffset_Y);
								static_canvas->K2_DrawText(calculation, bluecol, weaponname, false, true);
							}
						}
					}
					if (Settings::AmmoESP) {
						auto ammo = actor->CurrentWeapon()->GetMagazineAmmoCount();
						auto clipammo = actor->CurrentWeapon()->GetBulletsPerClip();
						if (ammo && clipammo) {
							static char ammoesp[128];
							static wchar_t wammoesp[128];
							sprintf(ammoesp, xorstr("Ammo: %d/%d"), ammo, clipammo);
							AnsiToWide(ammoesp, wammoesp);
							TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wammoesp)).y + 10;
							calculation = Vector2(TextOffset_X, TextOffset_Y);
							static_canvas->K2_DrawText(calculation, redcol, wammoesp, false, true);
						}
					}
					//not ud
					/*auto tier = actor->CurrentWeapon()->WeaponData()->Tier();
								static char tieresp[128];
								static wchar_t wtieresp[128];
								sprintf(tieresp, xorstr("%s"), tier);
								AnsiToWide(tieresp, wtieresp);
								TextOffset_Y += static_canvas->K2_TextSize(wtieresp).y + 10;
								calculation = Vector2(TextOffset_X, TextOffset_Y);
								static_canvas->K2_DrawText(calculation, GetItemColor(tier), wtieresp, false, true);*/
				}
				
				
				

				Vector2 ChestAtLeft = PlayerController->WorldToScreen(actor->GetBone(37));
				Vector2 ChestAtRight = PlayerController->WorldToScreen(actor->GetBone(8));
				Vector2 Chest = { ChestAtLeft.x + (ChestAtRight.x - ChestAtLeft.x) / 2, ChestAtLeft.y };
				ue::FLinearColor Color = ue::FLinearColor(1.f, 1.f, 0.f, 1.f);
				if (Settings::SkeletonESP) {
					Vector2 Neck = PlayerController->WorldToScreen(actor->GetBone(66));

					Vector2 LeftShoulder = PlayerController->WorldToScreen(actor->GetBone(93));
					Vector2 RightShoulder = PlayerController->WorldToScreen(actor->GetBone(9));
					Vector2 LeftElbow = PlayerController->WorldToScreen(actor->GetBone(94));
					Vector2 RightElbow = PlayerController->WorldToScreen(actor->GetBone(10));
					Vector2 LeftHand = PlayerController->WorldToScreen(actor->GetBone(100));
					Vector2 RightHand = PlayerController->WorldToScreen(actor->GetBone(99));
					Vector2 LeftLeg = PlayerController->WorldToScreen(actor->GetBone(76));
					Vector2 RightLeg = PlayerController->WorldToScreen(actor->GetBone(69));
					Vector2 LeftThigh = PlayerController->WorldToScreen(actor->GetBone(82));
					Vector2 RightThigh = PlayerController->WorldToScreen(actor->GetBone(75));
					Vector2 LeftFoot = PlayerController->WorldToScreen(actor->GetBone(78));
					Vector2 RightFoot = PlayerController->WorldToScreen(actor->GetBone(71));
					Vector2 LeftFeet = PlayerController->WorldToScreen(actor->GetBone(85));
					Vector2 RightFeet = PlayerController->WorldToScreen(actor->GetBone(84));
					Vector2 LeftFeetFinger = PlayerController->WorldToScreen(actor->GetBone(81));
					Vector2 RightFeetFinger = PlayerController->WorldToScreen(actor->GetBone(74));
					Vector2 Bottom = PlayerController->WorldToScreen(actor->GetBone(0));
					Vector2 Pelvis = PlayerController->WorldToScreen(actor->GetBone(2));


					static_canvas->K2_DrawLine(head_w2s, Neck, 2, Color);
					static_canvas->K2_DrawLine(Neck, Chest, 2, Color);
					static_canvas->K2_DrawLine(Chest, Pelvis, 2, Color);
					static_canvas->K2_DrawLine(Chest, LeftShoulder, 2, Color);
					static_canvas->K2_DrawLine(Chest, RightShoulder, 2, Color);
					static_canvas->K2_DrawLine(LeftShoulder, LeftElbow, 2, Color);
					static_canvas->K2_DrawLine(RightShoulder, RightElbow, 2, Color);
					static_canvas->K2_DrawLine(LeftElbow, LeftHand, 2, Color);
					static_canvas->K2_DrawLine(RightElbow, RightHand, 2, Color);
					static_canvas->K2_DrawLine(Pelvis, LeftLeg, 2, Color);
					static_canvas->K2_DrawLine(Pelvis, RightLeg, 2, Color);
					static_canvas->K2_DrawLine(LeftLeg, LeftThigh, 2, Color);
					static_canvas->K2_DrawLine(RightLeg, RightThigh, 2, Color);
					static_canvas->K2_DrawLine(LeftThigh, LeftFoot, 2, Color);
					static_canvas->K2_DrawLine(RightThigh, RightFoot, 2, Color);
					static_canvas->K2_DrawLine(LeftFoot, LeftFeet, 2, Color);
					static_canvas->K2_DrawLine(RightFoot, RightFeet, 2, Color);
					static_canvas->K2_DrawLine(LeftFeet, LeftFeetFinger, 2, Color);
					static_canvas->K2_DrawLine(RightFeet, RightFeetFinger, 2, Color);

				}
				if (Settings::LinesESP) {
					static_canvas->K2_DrawLine(Vector2(width / 2, height), Chest, 2, Color);
				}





			}
		}

	}
}
Vector3 OriginalLocation;
Vector3 OriginalRotation;
bool once = true;
bool once2 = true;
Vector3 rot;
void(*o_GetViewPoint)(uintptr_t, ue::FMinimalViewInfo*, BYTE) = nullptr;
void hk_GetViewPoint(uintptr_t this_LocalPlayer, ue::FMinimalViewInfo* OutViewInfo, BYTE StereoPass)
{
	o_GetViewPoint(this_LocalPlayer, OutViewInfo, StereoPass);
	if (sdkUssage->isValidPointer(uintptr_t(LocalPawno)))
	{
		//static bool GetCameraLocation = true;
		//static Vector3 NewLocation;

		//if (GetCameraLocation) {
		//	// Set our new location to the original spot once
		//	NewLocation = OutViewInfo->Location;
		//	GetCameraLocation = false;
		//}

		if (Settings::SilentAim)
		{
			if (PlayerController->IsInputKeyDown(ue::FKey(RBKey)))
			{
				OutViewInfo->Rotation = OriginalRotation;
				OutViewInfo->Location = OriginalLocation;
				//OutViewInfo->Location = rot;
				
			}

			/*if (safe_call(GetAsyncKeyState)('W')) NewLocation.x += 5.f;
			else if (safe_call(GetAsyncKeyState)('S')) NewLocation.x -= 5.f;
			else if (safe_call(GetAsyncKeyState)('A')) NewLocation.y += 5.f;
			else if (safe_call(GetAsyncKeyState)('D')) NewLocation.y -= 5.f;
			else if (safe_call(GetAsyncKeyState)(VK_SPACE)) NewLocation.z += 5.f;
			else if (safe_call(GetAsyncKeyState)(VK_SHIFT)) NewLocation.z -= 5.f;

			OutViewInfo->Location = NewLocation;*/

			//OutViewInfo->Location = OriginalLocation;
		}
		//OutViewInfo->FOV = 1000;


	}
}
void(*o_GetPlayerViewPoint)(uintptr_t, Vector3*, Vector3*) = nullptr;
void hk_GetPlayerViewPoint(uintptr_t this_PlayerController, Vector3* Location, Vector3* Rotation) {
	
	o_GetPlayerViewPoint(this_PlayerController, Location, Rotation);
	OriginalLocation = *Location;
	OriginalRotation = *Rotation;
	//if (once) { MessageBox(0, L"ud", 0, 0); once = false; }
	if (sdkUssage->isValidPointer(uintptr_t(LocalPawno)))
	{
		

		if (Settings::SilentAim) {
			if (PlayerController->IsInputKeyDown(ue::FKey(RBKey)))
			{
				auto rootHead = TargetPawno->GetBone(68);
				Vector3 camloc = *Location;
				Vector3 VectorPos;
				VectorPos.x = rootHead.x - camloc.x;
				VectorPos.y = rootHead.y - camloc.y;
				VectorPos.z = rootHead.z - camloc.z;
				float distance = (double)(sqrtf(VectorPos.x * VectorPos.x + VectorPos.y * VectorPos.y + VectorPos.z * VectorPos.z));
				
				rot.x = -((acosf(VectorPos.z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
				rot.y = atan2f(VectorPos.y, VectorPos.x) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
				rot.z = 0;
				*Rotation = rot;
				
			}
			
		}
	}
	
}
float(*CalculateReloadSpeedOriginal)(AWeapon*, float*) = nullptr;
auto CalculateReloadSpeedHook(AWeapon* Weapon, float* a2) //__m128 __fastcall sub_7FF660B36E80(__int64 a1)
{
	return FLT_MAX;
	return CalculateReloadSpeedOriginal(Weapon, a2);
}
bool oncee = false;
bool onceee = false;
bool temponce = false;
bool initudhooker = true;


static uintptr_t storedPController;
static uintptr_t storedPCurrentWeapon;
static uintptr_t storedPLocalPlayer;
bool hookplayanama = false;
bool calcc = false;
bool hookgetactorrotation = true;
bool hookdis = true;
bool hookdiss = true;
bool hookdisss = true;
bool hookdissss = true;
void VirtualTableFunctionSwap(void* VTable, void* FunctionToSwap, void** pOriginal, int Index)
{
	DWORD Old;

	void* pVTableFunction = (void*)((uint64_t)VTable + Index);
	*pOriginal = *(PVOID*)(pVTableFunction);

	VirtualProtectEx((HANDLE)-1, pVTableFunction, 8, PAGE_EXECUTE_READWRITE, &Old);
	*(PVOID*)pVTableFunction = FunctionToSwap;
	VirtualProtectEx((HANDLE)-1, pVTableFunction, 8, Old, &Old);
}
void DrawTransition(uintptr_t this_, uintptr_t Canvas) {
	if (!Canvas) {
		return DrawTransition(this_, Canvas);
	}
	static_canvas = (UCanvas*)Canvas;

	actorloop();



	auto uworld = ((GWorld*)(*(uintptr_t*)(ue::cached::signatures::GWorld)));
	auto LocalPlayer = uworld->OwningGameInstance()->LocalPlayers()->LocalPlayer();
	
	//GetViewpoint
	if (storedPLocalPlayer != (uintptr_t)LocalPlayer)
	{
		////DO YOUR HOOK
		storedPLocalPlayer = (uintptr_t)LocalPlayer;
		//std::cout << "ud\n";

		hookdisss = true;

	}
	if (storedPLocalPlayer == (uintptr_t)LocalPlayer && hookdisss) {

		if (LocalPlayer) {
			void** LocalPlayer_VTable = *(void***)(LocalPlayer);
			DWORD OldProtection;
			safe_call(VirtualProtect)(&LocalPlayer_VTable[88], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
			o_GetViewPoint = decltype(o_GetViewPoint)(LocalPlayer_VTable[88]);
			LocalPlayer_VTable[88] = &hk_GetViewPoint;
			safe_call(VirtualProtect)(&LocalPlayer_VTable[88], 8, OldProtection, &OldProtection);
			
		}

		hookdisss = false;
	}

	//CalculateReloadSpeed
	if (storedPCurrentWeapon != (uintptr_t)LocalPawno->CurrentWeapon())
	{
		
		storedPCurrentWeapon = (uintptr_t)LocalPawno->CurrentWeapon();
		//std::cout << "ud\n";

		hookdiss = true;

	}
	if (Settings::InstantReload && storedPCurrentWeapon == (uintptr_t)LocalPawno->CurrentWeapon() && hookdiss) {

		if (LocalPawno->CurrentWeapon()) {
			void** CurrentWeapon_VTable = *(void***)(LocalPawno->CurrentWeapon());
			DWORD OldProtection;
			safe_call(VirtualProtect)(&CurrentWeapon_VTable[296], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
			CalculateReloadSpeedOriginal = decltype(CalculateReloadSpeedOriginal)(CurrentWeapon_VTable[296]);
			CurrentWeapon_VTable[296] = &CalculateReloadSpeedHook;
			safe_call(VirtualProtect)(&CurrentWeapon_VTable[296], 8, OldProtection, &OldProtection);
			
		}

		hookdiss = false;
	}

	
	//GetPlayerViewpoint
	if (storedPController != (uintptr_t)LocalPlayer->PlayerController())
	{
		
		storedPController = (uintptr_t)LocalPlayer->PlayerController();
		//std::cout << "ud\n";
		hookdis = true;

	}

	if (Settings::SilentAim && storedPController == (uintptr_t)LocalPlayer->PlayerController() && hookdis) {
		
		
		void** PlayerController_VTable = *(void***)(LocalPlayer->PlayerController());
		DWORD OldProtection;
		safe_call(VirtualProtect)(&PlayerController_VTable[245], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
		o_GetPlayerViewPoint = decltype(o_GetPlayerViewPoint)(PlayerController_VTable[245]);
		PlayerController_VTable[245] = &hk_GetPlayerViewPoint;
		safe_call(VirtualProtect)(&PlayerController_VTable[245], 8, OldProtection, &OldProtection);
		hookdis = false;
	}





	//if (safe_call(GetAsyncKeyState)(VK_INSERT) & 1)
	if (PlayerController->WasInputKeyJustPressed(ue::FKey(InsertKey)))
	{
		ShowMenu = !ShowMenu;
	}

	static_canvas->K2_DrawLine(Vector2(width / 2 + 5, height / 2), Vector2(width / 2 + 10.f, height / 2), 3, { 1.f, 0.f, 0.f, 1.f });
	static_canvas->K2_DrawLine(Vector2(width / 2 - 5, height / 2), Vector2(width / 2 - 10.f, height / 2), 3, { 1.f, 0.f, 0.f, 1.f });
	static_canvas->K2_DrawLine(Vector2(width / 2, height / 2 + 5), Vector2(width / 2, height / 2 + 10.f), 3, { 1.f, 0.f, 0.f, 1.f });
	static_canvas->K2_DrawLine(Vector2(width / 2, height / 2 - 5), Vector2(width / 2, height / 2 - 10.f), 3, { 1.f, 0.f, 0.f, 1.f });

	Pasted_CircleOutline(Vector2(width / 2, height / 2), FovSize, { 0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f });
	DrawCircle(static_canvas, width / 2, height / 2, FovSize, 1450, ue::FLinearColor(0,0,1,1));
	if (ShowMenu) {
		DrawMenu();
	}


	return DrawTransitionOriginal(this_, Canvas);
}
VOID Main()
{
	
	/*AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);*/


	
		ue::cached::Base = sdkUssage->GetGameBase();

		ue::cached::signatures::GWorld = sdkUssage->PatternScan(ue::cached::Base, xorstr("48 89 05 ? ? ? ? 48 8B 4B 78"), 7, true); if (!ue::cached::signatures::GWorld) safe_call(MessageBox)(0, xorstr(L"UWorld"), 0, 0);
		ue::cached::signatures::GetBoneMatrix = sdkUssage->PatternScan(ue::cached::Base, xorstr("E8 ? ? ? ? 0F 10 40 68"), 5, true); if (!ue::cached::signatures::GetBoneMatrix) safe_call(MessageBox)(0, xorstr(L"GetBoneMatrix"), 0, 0);
		ue::cached::signatures::ProjectWorldToScreen = sdkUssage->PatternScan(ue::cached::Base, xorstr("E8 ? ? ? ? 4C 8D 5C 24 ? 41 88 06 49 8B 5B 20 49 8B 73 30 49 8B 7B 38"), 5, true); if (!ue::cached::signatures::ProjectWorldToScreen) safe_call(MessageBox)(0, xorstr(L"ProjectWorldToScreen"), 0, 0);
		ue::cached::signatures::FreeFn = sdkUssage->PatternScan(ue::cached::Base, xorstr("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0"), 0, false); if (!ue::cached::signatures::FreeFn) safe_call(MessageBox)(0, xorstr(L"FreeFn"), 0, 0);
		ue::cached::signatures::GetNameByIndex = sdkUssage->PatternScan(ue::cached::Base, xorstr("48 89 5C 24 08 48 89 74 24 18 48 89 7C 24 20 41 56 48 81 EC 30"), 0, false); if (!ue::cached::signatures::GetNameByIndex) safe_call(MessageBox)(0, xorstr(L"GetNameByIndex"), 0, 0);
		ue::classes::objects = (ue::classes::GObjects*)sdkUssage->PatternScan(ue::cached::Base, xorstr("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1"), 7, true); if (!ue::classes::objects) safe_call(MessageBox)(0, xorstr(L"GObjects"), 0, 0);

		ue::cached::objects::camera::GetCameraLocation = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.PlayerCameraManager.GetCameraLocation")); if (!ue::cached::objects::camera::GetCameraLocation) return;
		ue::cached::objects::camera::GetCameraRotation = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.PlayerCameraManager.GetCameraRotation")); if (!ue::cached::objects::camera::GetCameraRotation) return;
		ue::cached::objects::camera::GetFOVAngle = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.PlayerCameraManager.GetFOVAngle")); if (!ue::cached::objects::camera::GetCameraRotation) return;

		ue::cached::objects::render::Font = (ue::classes::UObject*)find::FindObject(xorstr(L"/Engine/EngineFonts/Roboto.Roboto")); if (!ue::cached::objects::render::Font) return;
		ue::cached::objects::render::K2_DrawLine = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Canvas.K2_DrawLine")); if (!ue::cached::objects::render::K2_DrawLine) return;
		ue::cached::objects::render::K2_DrawBox = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Canvas.K2_DrawBox")); if (!ue::cached::objects::render::K2_DrawBox) return;
		ue::cached::objects::render::K2_DrawText = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Canvas.K2_DrawText")); if (!ue::cached::objects::render::K2_DrawText) return;
		ue::cached::objects::render::K2_TextSize = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Canvas.K2_TextSize")); if (!ue::cached::objects::render::K2_DrawBox) return;

		ue::cached::objects::actor::FortPlayerPawnAthena = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortPlayerPawnAthena")); if (!ue::cached::objects::actor::FortPlayerPawnAthena) return;
		ue::cached::objects::actor::ClientSetRotation = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Controller.ClientSetRotation")); if (!ue::cached::objects::actor::ClientSetRotation) return;
		ue::cached::objects::actor::GetPlayerName = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.PlayerState.GetPlayerName")); if (!ue::cached::objects::actor::GetPlayerName) return;
		ue::cached::objects::actor::ApplyPawnHighlight = (ue::classes::UObject*)find::FindObject(xorstr(L"PlayerPawn_Athena.PlayerPawn_Athena_C.ApplyPawnHighlight")); if (!ue::cached::objects::actor::ApplyPawnHighlight) return;
		ue::cached::objects::actor::Fov = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.PlayerController.FOV")); if (!ue::cached::objects::actor::Fov) return;
		ue::cached::objects::actor::SetMouseLocation = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.PlayerController.SetMouseLocation")); if (!ue::cached::objects::actor::SetMouseLocation) return;
		ue::cached::objects::FortProjectileBase = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortProjectileBase")); if (!ue::cached::objects::FortProjectileBase) return;
		ue::cached::objects::AFortAthenaZipline = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortAthenaZipline")); if (!ue::cached::objects::AFortAthenaZipline) return;
		ue::cached::objects::FortRangedWeaponStats = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortRangedWeaponStats")); if (!ue::cached::objects::FortRangedWeaponStats) return;
		
		ue::cached::objects::K2_GetActorRotation = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Actor.K2_GetActorRotation")); if (!ue::cached::objects::K2_GetActorRotation) return;
		
		ue::cached::objects::actor::isHiddingInProp = (ue::classes::UObject*)find::FindObject(xorstr(L"PlayerPawn_Athena.PlayerPawn_Athena_C.isHiddingInProp")); if (!ue::cached::objects::actor::isHiddingInProp) return;
		ue::cached::objects::actor::SetCharacterBodyVisibilityForPossession = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortPlayerPawnAthena.SetCharacterBodyVisibilityForPossession")); if (!ue::cached::objects::actor::SetCharacterBodyVisibilityForPossession) return;
		ue::cached::FortKismetLibrary = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortKismetLibrary")); if (!ue::cached::FortKismetLibrary) return;
		ue::cached::KismetStringLibrary = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.KismetStringLibrary")); if (!ue::cached::KismetStringLibrary) return;
		ue::cached::KismetMathLibrary = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.KismetMathLibrary")); if (!ue::cached::KismetMathLibrary) return;
		ue::cached::Conv_StringToName = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.KismetStringLibrary.Conv_StringToName")); if (!ue::cached::Conv_StringToName) return;
		ue::cached::Cos = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.KismetMathLibrary.Cos")); if (!ue::cached::Cos) return;
		ue::cached::Sin = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.KismetMathLibrary.Sin")); if (!ue::cached::Sin) return;

		ue::cached::objects::actor::K2_PayBuildingResourceCost = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortKismetLibrary.K2_PayBuildingResourceCost")); if (!ue::cached::objects::actor::K2_PayBuildingResourceCost) return;
		ue::cached::objects::actor::GetVehicle = (ue::classes::UObject*)find::FindObject(xorstr(L"FortniteGame.FortPlayerPawn.GetVehicle")); if (!ue::cached::objects::actor::GetVehicle) return;
		ue::cached::objects::K2_TeleportTo = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Actor.K2_TeleportTo")); if (!ue::cached::objects::K2_TeleportTo) return;
		ue::cached::objects::K2_SetActorLocation = (ue::classes::UObject*)find::FindObject(xorstr(L"Engine.Actor.K2_SetActorLocation")); if (!ue::cached::objects::K2_SetActorLocation) return;

		InsertKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(xorstr(L"Insert")) }, 0 };
		LBKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(xorstr(L"LeftMouseButton")) }, 0 };
		RBKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(xorstr(L"RightMouseButton")) }, 0 };
		F7Key = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(xorstr(L"F7")) }, 0 };
		

		
		FNTool* sdk = new FNTool();
		sdk->Initialize((uintptr_t)ue::classes::objects, ue::cached::signatures::GetNameByIndex, ue::cached::signatures::FreeFn);

		ue::cached::offsets::OwningGameInstance = sdk->FindOffset("World", "OwningGameInstance");
		ue::cached::offsets::Levels = sdk->FindOffset("World", "Levels");
		ue::cached::offsets::AcknowledgedPawn = sdk->FindOffset("PlayerController", "AcknowledgedPawn");
		ue::cached::offsets::PlayerCameraManager = sdk->FindOffset("PlayerController", "PlayerCameraManager");
		ue::cached::offsets::PlayerState = sdk->FindOffset("Pawn", "PlayerState");
		ue::cached::offsets::bADSWhileNotOnGround = sdk->FindOffset("FortPlayerPawnAthena", "bADSWhileNotOnGround");
		ue::cached::offsets::CurrentWeapon = sdk->FindOffset("FortPawn", "CurrentWeapon");
		ue::cached::offsets::TeamIndex = sdk->FindOffset("FortPlayerStateAthena", "TeamIndex");
		ue::cached::offsets::WeaponData = sdk->FindOffset("FortWeapon", "WeaponData");
		ue::cached::offsets::DisplayName = sdk->FindOffset("FortItemDefinition", "DisplayName");
		ue::cached::offsets::Mesh = sdk->FindOffset("Character", "Mesh");
		ue::cached::offsets::RootComponent = sdk->FindOffset("Actor", "RootComponent");
		ue::cached::offsets::RelativeLocation = sdk->FindOffset("SceneComponent", "RelativeLocation");
		ue::cached::offsets::LastFireTime = sdk->FindOffset("FortWeapon", "LastFireTime");
		ue::cached::offsets::AmmoCount = sdk->FindOffset("FortWeapon", "AmmoCount");
		ue::cached::offsets::LastFireTimeVerified = sdk->FindOffset("FortWeapon", "LastFireTimeVerified");
		ue::cached::offsets::Tier = sdk->FindOffset("FortItemDefinition", "Tier");

		auto UViewportClient = ((GWorld*)(*(uintptr_t*)(ue::cached::signatures::GWorld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer()->ViewportClient();
	
		void** DrawTransition_VTable = *(void***)(UViewportClient);
		DWORD OldProtection;
		safe_call(VirtualProtect)(&DrawTransition_VTable[110], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
		DrawTransitionOriginal = decltype(DrawTransitionOriginal)(DrawTransition_VTable[110]);
		DrawTransition_VTable[110] = &DrawTransition;
		safe_call(VirtualProtect)(&DrawTransition_VTable[110], 8, OldProtection, &OldProtection);
		
	
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason != DLL_PROCESS_ATTACH) return FALSE;

	Main();

	return TRUE;
}
