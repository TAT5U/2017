using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Home : MonoBehaviour 
{
		private enum State
	{
		FIRSTSTATE = 1,
		EARLYSTATE = 2,
		LATESTATE = 3,
		LASTSTATE = 4
	};


	public Gage gage;
	//public RepairGage rgage;
	private GameObject repair;

	private SpriteRenderer homeNow;
	public Sprite stateFirst, stateEarly, stateLate, stateLast;

	public bool attackFlg;

	public string str;


	// Use this for initialization
	void Start () 
	{
		homeNow = gameObject.GetComponent<SpriteRenderer>();
	}
	
	// Update is called once per frame
	void Update () 
	{

		if (Input.GetMouseButton(0)) 
		{
			Vector2 tapPt = Camera.main.ScreenToWorldPoint(Input.mousePosition);
			Collider2D col = Physics2D.OverlapPoint(tapPt);

			if (col) 
			{
				RaycastHit2D ray = Physics2D.Raycast(tapPt,-Vector2.up);
				if (ray) 
				{
					if (ray.collider != null) 
					{
						if (ray.collider.name == gameObject.name) 
						{
							if (!attackFlg) 
							{
								str = ray.collider.name.Substring(3);
								GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + str).gameObject.SetActive(true);
								GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + str).gameObject.SetActive(true);
								GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + str).gameObject.SetActive(true);
								GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + str).gameObject.SetActive(true);

																															

								gage.touchFlg = true;
							}
					
							
						}

					}
				}
			}
		}

	}
	void SpriteState(int flg)
	{
		if (flg == (int)State.FIRSTSTATE) 
		{
			homeNow.sprite = stateFirst;
		}
		else if (flg == (int)State.EARLYSTATE) 
		{
			homeNow.sprite = stateEarly;
		}
		else if (flg == (int)State.LATESTATE) 
		{
			homeNow.sprite = stateLate;
		}
		else if (flg == (int)State.LASTSTATE) 
		{
			homeNow.sprite = stateLast;
		}
	}
	void OnTriggerStay2D(Collider2D other)
	{
		if (other.gameObject.tag == "Enemy") 
		{
			print("aaa");
			attackFlg = true;
			GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageIcon" + str).gameObject.SetActive(false);
			GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageBackGround" + str).gameObject.SetActive(false);
			GameObject.Find("Canvas").transform.Find("Repair").transform.Find("Image" + str).gameObject.SetActive(false);
			GameObject.Find("Canvas").transform.Find("Repair").transform.Find("ImageFrame" + str).gameObject.SetActive(false);
			gage.gageFlg = true;
			gage.Damage();
		}
		else 
		{
			attackFlg = false;
		}
	}
}
