using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HPGage : MonoBehaviour 
{
	private enum State
	{
		FIRSTSTATE = 1,
		EARLYSTATE = 2,
		LATESTATE = 3,
		LASTSTATE = 4
	};

	private RectTransform rect;

	public GameObject homeObj;
		private float maxValue;
		private float t;
		public float gageSpeed;

		private bool attackFlg; 

	void Awake()
	{
		rect = transform.Find("Gage").gameObject.GetComponent<RectTransform>();

        Vector3 position = Camera.main.WorldToScreenPoint(homeObj.transform.position);

        RectTransform barRect = gameObject.GetComponent<RectTransform>();

        print(position);

        barRect.position = position; /*+ new Vector3(-50, 40, 0)*/;

        //gameObject.transform.localPosition = position;
        print(barRect.position);

        maxValue = rect.sizeDelta.x;
		t = 1.0f;

	}
	private void UpdateValue(float t)
	{
        if (rect == null)
        {
            return;
        }
		float x = Mathf.Lerp(0f, maxValue, t);
		rect.sizeDelta = new Vector2(x, rect.sizeDelta.y);
	}
	
	// Update is called once per frame
	void Update () 
	{

	}
	public void Damage()
	{
				t-=gageSpeed;
		UpdateValue(t);
		//gameObject.GetComponent<Image>().color = Color.red;

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
