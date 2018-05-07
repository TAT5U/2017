using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraManager : MonoBehaviour 
{
	[SerializeField]
	private GameObject start_;
	[SerializeField]
	private float cameraSpeed_ = 0.0f;

	[System.NonSerialized]
	public bool isWarp_ = false;

	public Vector3 startPos;

	private Vector3 targetPos_ = new Vector3(0.0f, 0.0f, 0.0f);

	private void Update()
	{
		if (!isWarp_) return;
		transform.position = Vector3.MoveTowards(transform.position, targetPos_, cameraSpeed_ * Time.deltaTime);

		if (transform.position.magnitude == targetPos_.magnitude)
		{
			GetComponentInChildren<CharacterManager>().isWarp_ = false;
			isWarp_ = false;
		}
	}

	public void SetCamera()
	{
		Vector3 pos = new Vector3(start_.transform.Find("Start").transform.position.x, start_.transform.Find("Start").transform.position.y, transform.position.z);
		transform.position = pos;
		startPos = pos;
	}

	public void SetCameraWarp(Vector3 targetPos)
	{
		targetPos_ = targetPos;
		isWarp_ = true;
	}
}
