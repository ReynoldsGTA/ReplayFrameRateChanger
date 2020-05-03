#include "plugin.h"
#include "CHud.h"
#include "CRideAnimData.h"
#include "CBike.h"
#include "tBikeHandlingData.h"

using namespace plugin;

bool checkHandling() {
	CVehicle *veh = FindPlayerVehicle(-1, false);
	if (veh && veh->m_nVehicleSubClass == VEHICLE_BIKE) {
		CBike *bike = reinterpret_cast<CBike *>(veh);
		tBikeHandlingData* bHandling = reinterpret_cast<tBikeHandlingData *>(bike->m_pBikeHandlingData);
		tHandlingData* handling = reinterpret_cast<tHandlingData *>(veh->m_pHandlingData);
	
		bool noMods = true;
		if (bike->m_nModelIndex == 522) {
			noMods = noMods && (handling->m_fMass == 400.0);
			noMods = noMods && (handling->m_fTurnMass == 200.0);
			noMods = noMods && (handling->m_fDragMult == 4.0);
			/*
			noMods = noMods && (bHandling->m_fLeanFwdCOM == 0.25);
			noMods = noMods && (bHandling->m_fLeanFwdForce == 0.10);
			noMods = noMods && (bHandling->m_fLeanBakCOM == 0.30);
			noMods = noMods && (bHandling->m_fLeanBakForce == 0.10);
			noMods = noMods && (bHandling->m_fMaxLean == 55.0);
			*/
		}

		if (!noMods) {
			return true;
		}
	}
	return false;
}

class ReplayFrameRateChanger {
public:
	ReplayFrameRateChanger() {
		static bool highFps = false;

		Events::gameProcessEvent += [] {
			if (KeyPressed(VK_F7)) {
				if (!highFps && !checkHandling()) {
					CHud::SetHelpMessage("Increased replay FPS", false, false, false);
					patch::SetChar(0x460578, 3);
					highFps = !highFps;
				}
				else {
					CHud::SetHelpMessage("Decreased replay FPS", false, false, false);
					patch::SetChar(0x460578, 26);
					highFps = !highFps;
				}
				
			}	

		};
    }
} replayFrameRateChanger;
