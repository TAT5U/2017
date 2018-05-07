using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour 
{
	[SerializeField]private MissionManager missionManager_;
    [SerializeField]private TimeController m_timeController;
	[SerializeField]private LifeController life_;

	private TileMapLoader 	 tileMap_;
	private CameraManager 	 mainCamera_;
	private CharacterManager player_;

    public GameObject countDown;

	private GameDataManager gameData_;
	private int rankCount_ = 0, stageCount_ = 0;

	private bool isStart_ = false;

	private bool isAnimation_ = false;

	private int[] bitValue = new int[] { 0x001, 0x002, 0x004 };

    public bool IsStart { get { return isStart_; } }

	private void Awake () 
	{
		Initialize();

		rankCount_ = (int)gameData_.m_selectRank;
		stageCount_ = (int)gameData_.m_selectButton;
		tileMap_.Create(rankCount_, stageCount_);
		mainCamera_.SetCamera();

		missionManager_.CreateMission(gameData_);
	}

	private void Initialize()
	{
		tileMap_ 	= GetComponentInChildren<TileMapLoader>();
		mainCamera_ = GetComponentInChildren<CameraManager>();
		player_ 	= GetComponentInChildren<CharacterManager>();

		gameData_ = GameDataManager.Instance;
	}

	private void Update () 
	{
		if (Application.platform == RuntimePlatform.Android || Application.platform == RuntimePlatform.IPhonePlayer)
		{
			if ((Input.GetTouch(0).phase == TouchPhase.Ended) && !isStart_)
			{
				missionManager_.Fade();
			}
            if(countDown.GetComponent<count>().countDownEnd && !isStart_)
            {
                isStart_ = true;
            }
		}
		else if(Application.platform == RuntimePlatform.WindowsEditor)
		{
            if ((Input.GetMouseButtonUp(0)) && !isStart_)
            {
                missionManager_.Fade();
            }
            if (countDown.GetComponent<count>().countDownEnd && !isStart_)
            {
                isStart_ = true;
            }
        }



        // クリア時
        if (player_.isClear_)
        {
			gameData_.m_gameTime = m_timeController.TimeCount;
            
			int rankCount = (int)gameData_.m_selectRank * 5;
            int clearStar = rankCount + (int)gameData_.m_selectButton;

			float second = float.Parse(missionManager_.StageGoalTime(gameData_, 0));
			float minute = float.Parse(missionManager_.StageGoalTime(gameData_, 1));
			float time = (minute * 60) + second;

			gameData_.m_starData[clearStar] = 1;

			if (life_.CurrentLife >= 2 || missionManager_.starFlg_[1] >= 1)
			{
				gameData_.m_starData[clearStar] += 2;	
			}

			if (time >= m_timeController.TimeCount || missionManager_.starFlg_[2] >= 1)
			{
				gameData_.m_starData[clearStar] += 4;
			}

			if (gameData_.LoadStarOfSelectStage(clearStar) <= gameData_.m_starData[clearStar])
			{
				gameData_.SaveStarOfSelectStage(clearStar);
			}

            FadeManager.Instance.m_sceneName = "Scenes/ResultScene";
            FadeManager.Instance.FadeOut();
        }
    }

	public void ChangeHP(bool flg)
	{
		isAnimation_ = flg;
	}
}
