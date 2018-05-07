using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TransformManager : MonoBehaviour 
{
	[SerializeField]private Camera mainCamera_;

	private void Start()
	{
		Vector3 pos = mainCamera_.transform.position;
		pos.z = transform.position.z;

		transform.position = pos;
	}
}
