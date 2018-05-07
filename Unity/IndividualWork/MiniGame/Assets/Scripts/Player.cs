using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {

    public float jumpPower;

	// Use this for initialization
	void Start ()
    {
	
	}
	
	// Update is called once per frame
	void Update ()
    {
		if (Application.platform == RuntimePlatform.IPhonePlayer) 
		{
			if (Input.GetTouch (0).phase == TouchPhase.Moved) 
			{
				GetComponent<Rigidbody> ().velocity = new Vector3 (0, jumpPower, 0);
			}
		}
		else 
		{
			if (Input.GetKeyDown(KeyCode.Space)) 
			{
				GetComponent<Rigidbody> ().velocity = new Vector3 (0, jumpPower, 0);
			}
		}

	}

	void OnCollisionEnter (Collision other)
	{
		//シーンを読み込む (Application.LoadLevel)
		// ゲームオーバー
		Application.LoadLevel("GameOver");
		
	}
}
