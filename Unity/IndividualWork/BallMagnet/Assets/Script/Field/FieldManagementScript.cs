using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FieldManagementScript : MonoBehaviour 
{
	public Camera mainCamera;
	private Vector3 minPosition;
	private Vector3 maxPosition;


	public CreateManagementScript objectManagement;

	private int count = 0;
	
	// Update is called once per frame
	void Update () 
	{
		minPosition = new Vector3(transform.position.x, transform.position.y, transform.position.z + transform.localScale.z * 6);
		maxPosition = minPosition;

		if (mainCamera.transform.position.z >= transform.position.z + transform.localScale.z && count <= 0)
		{
			gameObject.GetComponent<FieldGeneratorScript>().FieldGenerateCall(minPosition);

			objectManagement.SetVector(minPosition, maxPosition + new Vector3(0, 0, transform.localScale.z * 4));
			count++;
		}

		if (minPosition.z < mainCamera.transform.position.z)
		{
			Destroy(gameObject);
		}
	}
}
