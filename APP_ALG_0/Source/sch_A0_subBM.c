//================================================================================
#include "INF_default.h"
//================================================================================
#include "INF_EQ_Enum.h"
#include "INF_User_Parameter.h"
#include "INF_sch_prm_FBTPM.h"
//================================================================================


//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================

BOOL SCHEDULER_CONTROL_Chk_BM_FREE_ALL( int ch ) {
	int i;
	for ( i = 0 ; i < _SCH_PRM_GET_MODULE_SIZE( ch ) ; i++ ) {
		if ( _SCH_MODULE_Get_BM_WAFER( ch , i + 1 ) > 0 ) return FALSE;
	}
	return TRUE;
}

//==========================================================================================================================

BOOL SCHEDULER_CONTROL_Chk_BM_FULL_ALL( int ch ) {
	int i;
	for ( i = 0 ; i < _SCH_PRM_GET_MODULE_SIZE( ch ) ; i++ ) {
		if ( _SCH_MODULE_Get_BM_WAFER( ch , i + 1 ) <= 0 ) {
			if ( _SCH_PRM_GET_DFIM_SLOT_NOTUSE( ch , i+1 ) ) continue; // 2018.04.03
			return FALSE;
		}
	}
	return TRUE;
}


//==========================================================================================================================

int SCHEDULER_CONTROL_Chk_BM_HAS_COUNT( int ch , int checksts ) {
	int i , k = 0;
	for ( i = _SCH_PRM_GET_MODULE_SIZE( ch ) ; i >= 1 ; i-- ) {
		if ( _SCH_MODULE_Get_BM_WAFER( ch , i ) > 0 ) {
			if ( checksts == -1 ) {
				k++;
			}
			else {
				if ( _SCH_MODULE_Get_BM_STATUS( ch , i ) == checksts ) {
					k++;
				}
			}
		}
	}
	return k;
}

//==========================================================================================================================

int SCHEDULER_CONTROL_Chk_BM_FREE_COUNT( int ch ) {
	int i , k = 0;
	for ( i = _SCH_PRM_GET_MODULE_SIZE( ch ) ; i >= 1 ; i-- ) {
		if ( _SCH_MODULE_Get_BM_WAFER( ch , i ) <= 0 ) {
			if ( _SCH_PRM_GET_DFIM_SLOT_NOTUSE( ch , i ) ) continue; // 2018.04.03
			k++;
		}
	}
	return k;
}

//==========================================================================================================================

int SCHEDULER_CONTROL_Chk_BM_FREE_DBL( int ch ) { // 2015.07.02
	int i , k = 0;
	for ( i = 0 ; i < _SCH_PRM_GET_MODULE_SIZE( ch ) ; i++ ) {
		//
		if ( _SCH_MODULE_Get_BM_WAFER( ch , i + 1 ) <= 0 ) {
			if ( _SCH_MODULE_Get_BM_WAFER( ch , i + 2 ) <= 0 ) {
				if ( !_SCH_PRM_GET_DFIM_SLOT_NOTUSE( ch , i+1 ) ) { // 2018.04.03
					if ( !_SCH_PRM_GET_DFIM_SLOT_NOTUSE( ch , i+2 ) ) { // 2018.04.03
						k++;
					}
				}
			}
		}
		//
		i++;
	}
	return k;
}

//==========================================================================================================================

