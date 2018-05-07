using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Gage : MonoBehaviour 
{
	// 識別子
	private enum State
	{
		FIRSTSTATE = 1,
		EARLYSTATE = 2,
		LATESTATE = 3,
		LASTSTATE = 4
	};


	// 家
	public GameObject homeObj;
	public Home objCode;

	private float t=1.0f;

	public bool gageFlg, touchFlg;

	// Use this for initialization
	void Start () 
	{

	}
	
	// Update is called once per frame
	void Update () 
	{
			if (gageFlg==true && objCode.attackFlg==false && touchFlg==true) 
			{
				//現在の値を取得
				t = gameObject.GetComponent<Image>().fillAmount += 0.002f;

				// 修復度にあったスプライトを適用
				if (t >= 1.0f)
				{
					homeObj.SendMessage("SpriteState", (int)State.FIRSTSTATE);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + objCode.str).gameObject.SetActive(false);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + objCode.str).gameObject.SetActive(false);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + objCode.str).gameObject.SetActive(false);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + objCode.str).gameObject.SetActive(false);
					gageFlg = false;
					touchFlg = false;
				}
				else if (t <= 0.99f && t >= 0.30f) 
				{
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + objCode.str).gameObject.SetActive(true);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + objCode.str).gameObject.SetActive(true);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + objCode.str).gameObject.SetActive(true);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + objCode.str).gameObject.SetActive(true);
					homeObj.SendMessage("SpriteState", (int)State.EARLYSTATE);
				}
				else if (t <= 0.29f && t >= 0.01f) 
				{
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + objCode.str).gameObject.SetActive(true);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + objCode.str).gameObject.SetActive(true);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + objCode.str).gameObject.SetActive(true);
					GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + objCode.str).gameObject.SetActive(true);
					homeObj.SendMessage("SpriteState", (int)State.LATESTATE);
				}
				//break;
			}
			else 
			{
				print(gageFlg);
				print(objCode.attackFlg);
				print(touchFlg);

				GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + objCode.str).gameObject.SetActive(false);
				GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + objCode.str).gameObject.SetActive(false);
				GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + objCode.str).gameObject.SetActive(false);
				GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + objCode.str).gameObject.SetActive(false);
				touchFlg = false;
			}
	}


	// ダメージ
	public void Damage()
	{
		//現在の値を取得
		t = gameObject.GetComponent<Image>().fillAmount -= 0.002f;

		if (t <= 0.99f && t >= 0.30f) 
		{
			homeObj.SendMessage("SpriteState", (int)State.EARLYSTATE);
		}
		else if (t <= 0.29f && t >= 0.01f) 
		{
			homeObj.SendMessage("SpriteState", (int)State.LATESTATE);
		}
		else if (t <= 0.0f)  
		{
			homeObj.SendMessage("SpriteState", (int)State.LASTSTATE);
		}
	}
}
