using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RepairGage : MonoBehaviour {


		private enum State
	{
		FIRSTSTATE = 1,
		EARLYSTATE = 2,
		LATESTATE = 3,
		LASTSTATE = 4
	};


public bool gageFlg, touchFlg;
	public Home objCode;

		// 家
	public GameObject homeObj;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

/*
					if (gageFlg && !objCode.attackFlg && touchFlg) 
			{
				//現在の値を取得
				t = gameObject.GetComponent<Image>().fillAmount += 0.0001f;

				// 修復度にあったスプライトを適用
				if (t >= 1.0f)
				{
					homeObj.SendMessage("SpriteState", (int)State.FIRSTSTATE);
					//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + objCode.str).gameObject.SetActive(false);
					//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + objCode.str).gameObject.SetActive(false);
					//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + objCode.str).gameObject.SetActive(false);
					//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + objCode.str).gameObject.SetActive(false);
					gageFlg = false;
					touchFlg = false;
				}
				else if (t <= 0.99f && t >= 0.30f) 
				{
					homeObj.SendMessage("SpriteState", (int)State.EARLYSTATE);
				}
				else if (t <= 0.29f && t >= 0.01f) 
				{
					homeObj.SendMessage("SpriteState", (int)State.LATESTATE);
				}
			}
			else 
			{
				print(objCode.str);
				//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + objCode.str).gameObject.SetActive(false);
				//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + objCode.str).gameObject.SetActive(false);
				//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + objCode.str).gameObject.SetActive(false);
				//GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + objCode.str).gameObject.SetActive(false);
				touchFlg = false;
			}
			*/
		
	}
}
