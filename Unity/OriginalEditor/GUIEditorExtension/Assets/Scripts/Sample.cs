using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sample : MonoBehaviour 
{
	[SerializeField]
	private FadeManager fade_;


	public ArrayList a = new ArrayList();
	private float t;
	private bool isb = false;
	public int[] ak = new int[5];
	public string[] st = new string[3];
	private bool isd = false;
	// Use this for initialization
	void Start () 
	{
		
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (Application.platform == RuntimePlatform.Android && !isd)
		{
			if (Input.GetTouch(0).tapCount == 1)
			{
				fade_.FadeStart();
				isd = true;
			}
			else if (Input.GetTouch(0).tapCount == 2)
			{
				fade_.FadeStart(1);
				isd = true;
			}
			else if (Input.GetTouch(0).tapCount >= 3)
			{
				fade_.FadeStart(2);
				isd = true;
			}
		}
		else
		{
			t += Time.deltaTime;
			if (t > 5 && !isd)
			{
				fade_.FadeStart();
				isd = true;
			}
		}
	}
}
