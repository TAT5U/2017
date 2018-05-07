using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MissionManager : MonoBehaviour 
{

	private const int kMaxButtonStage = 5;

	// privateでシリアライズすると"Unsupported Type GoalTime"とでた
	// [System.Serializable]を消すとインスペクタに表示されなくなるので注意
	// TODO: 原因理解 -> classは基本public
	[System.Serializable]
	public class GoalTime
	{
		public int minute = 0;
		public int second = 0;
	}

	[System.Serializable]
	private class MissionGoalTime
	{
		[SerializeField]
		private string rankName;
		public GoalTime[] time = new GoalTime[kMaxButtonStage];
	}

	[SerializeField]
	private Sprite star_;
	[SerializeField]
	private float speed_ = 0.0f;
	[SerializeField]
	private float delayTime_ = 0.0f;

	[SerializeField]
	private MissionGoalTime[] goalTime_ = new MissionGoalTime[10];


	private List<GameObject> mission_ = new List<GameObject>();

	private int missionCount_ = 0;

	private int[] bitValue_ = new int[] { 0x001, 0x002, 0x004 };

	// HACK: クソコード
	// 前回のフラグ取得
	[System.NonSerialized]
	public int[] starFlg_ = new int[] { 0, 0, 0 };

	public void CreateMission(GameDataManager gameData)
	{
		int rankCount = (int)gameData.m_selectRank * kMaxButtonStage;

		int clearStar = gameData.m_starData[rankCount + (int)gameData.m_selectButton];

		foreach (Transform child in transform)
		{
			mission_.Add(child.gameObject);
		}

		// ミッションの時間の設定
		// HACK: 要素数直打ち✗
		mission_[2].GetComponent<Text>().text = StageGoalTime(gameData).ToString();

		while (missionCount_ < mission_.Count)
		{
			if ((clearStar & bitValue_[missionCount_]) == bitValue_[missionCount_])
			{
				mission_[missionCount_].GetComponentInChildren<Image>().sprite = star_;
				starFlg_[missionCount_] = 1;
			}
			missionCount_++;
		}
	}

	public void Fade()
	{
		Vector3 pos = transform.position;
		pos.y += speed_;

		transform.position = pos;

		//if (pos.y > Screen.height) return;

		Invoke("Fade", delayTime_);
	}

	// 目標時間を返す
	public string StageGoalTime(GameDataManager gameData, int index = 999)
	{
		if (index <= 0) return goalTime_[(int)gameData.m_selectRank].time[(int)gameData.m_selectButton].minute.ToString();
		if (index > 0 && index < 10) return goalTime_[(int)gameData.m_selectRank].time[(int)gameData.m_selectButton].second.ToString();

		string timeData = "";
		int minuteData = goalTime_[(int)gameData.m_selectRank].time[(int)gameData.m_selectButton].minute;

		if (minuteData > 0)
		{
			timeData = goalTime_[(int)gameData.m_selectRank].time[(int)gameData.m_selectButton].minute.ToString() + "分";
		}
		timeData += goalTime_[(int)gameData.m_selectRank].time[(int)gameData.m_selectButton].second.ToString() + "秒";
		return timeData;
	}
}
