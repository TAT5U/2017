using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackGroundManager : MonoBehaviour 
{
	public Camera mainCamera_;
	public GameObject backGround_;

	private int createCount_ = 0;
	private Vector3 backGroundNewPosition_;

	private void Awake()
	{
		backGroundNewPosition_ = transform.Find("Ground3").transform.position;
	}

	// Update is called once per frame
	void Update () 
	{
		if (mainCamera_.WorldToScreenPoint(transform.position).x < mainCamera_.transform.position.x / 300 && !IsCreate())
		{
			CreateBackGround();
		}
		else if (transform.position.x + backGroundNewPosition_.x < mainCamera_.transform.position.x)
		{
			Destroy(gameObject);
		}
	}

	private bool IsCreate()
	{
		if (createCount_ <= 0)
		{
			createCount_++;
			return false;
		}
		return true;
	}

	private void CreateBackGround()
	{
		GameObject createGround = Instantiate(backGround_);
		backGroundNewPosition_.y = 0.0f;
		backGroundNewPosition_.z = 0.0f;
		createGround.transform.position = backGroundNewPosition_;
		createGround.transform.SetAsLastSibling();
		createGround.name = name;
	}
}
