using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectControllerScript : MonoBehaviour 
{
	public Camera mainCamera;

	void Update () 
	{
		if (gameObject.transform.position.z < mainCamera.transform.position.z || gameObject.transform.position.y < mainCamera.transform.position.y - 100)
		{
			Destroy(gameObject);
		}
	}
}
