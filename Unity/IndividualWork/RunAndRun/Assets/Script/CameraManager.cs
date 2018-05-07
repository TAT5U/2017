using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraManager : MonoBehaviour {

	[SerializeField]private Vector3 transValue_;

	// Update is called once per frame
	void Update()
	{
		transform.position += transValue_ * Time.deltaTime;
	}
}
