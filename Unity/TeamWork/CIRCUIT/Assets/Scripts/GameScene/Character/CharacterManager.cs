using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterManager : MonoBehaviour 
{
	public int colliderCount_ = 0;

	public Collider2D col_;

	[System.NonSerialized]
	public bool isClear_ = false;

	[System.NonSerialized]
	public bool isWarp_ = false;


	// HACK: EnterとExit2つも使ってるので良くない
	// 		 当たり判定は何か別の方法があったらそっちに変更
	private void OnTriggerEnter2D(Collider2D col)
	{
		if (col.name == "Warp" && !isWarp_)
		{
			isWarp_ = true;
			Vector3 pos = col.GetComponent<WarpManager>().Warp();
			pos.z = transform.parent.position.z;
			GetComponentInParent<CameraManager>().SetCameraWarp(pos);
		}
		else if (col.name == "Goal")
		{
			isClear_ = true;
			GameDataManager.Instance.isGameOver = false;
		}

		colliderCount_++;
	}

	private void OnTriggerExit2D(Collider2D col)
	{
		col_ = col;
		colliderCount_--;
	}
}
