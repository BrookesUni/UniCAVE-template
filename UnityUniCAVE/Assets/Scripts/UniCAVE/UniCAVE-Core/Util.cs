﻿//MIT License
//Copyright 2016-Present 
//Ross Tredinnick
//Brady Boettcher
//Benny Wysong-Grass
//University of Wisconsin - Madison Virtual Environments Group
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
//to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
//sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

using UnityEngine;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System;

namespace UniCAVE
{
    public static class Util
    {
        /// <summary>
        /// Return the machine name this instance is running on, which may be modified by command line options: <para/>
        /// overrideMachineName *name* changes machine name to *name* <para/>
        /// appendMachineName *suffix* adds *suffix* to original machine name
        /// </summary>
        ///
        
        private const int DefaultTimeoutTime = 20;
            
        public static string GetMachineName()
        {
            string overridden = Util.GetArg("overrideMachineName");
            if(overridden != null)
            {
				//Debug.Log("Get Machine Name: " + overridden);
                return overridden;
            }

            string appendMachineName = Util.GetArg("appendMachineName") ?? "";
            return Environment.MachineName + appendMachineName;
        }

        /// <summary>
        /// Used to increase performance of GetArg(...)
        /// </summary>
        private static Dictionary<string, string> _cachedArgs = new();

        /// <summary>
        /// Return the string following a certain string in the invocation, null if it doesn't exist
        /// </summary>
        /// <param name="name">parameter name to retrieve</param>
        public static string GetArg(string name)
        {
            if(Util._cachedArgs.ContainsKey(name))
                return Util._cachedArgs[name];

            string[] args = Environment.GetCommandLineArgs();

            for(int i = 0; i < args.Length; i++)
                if(args[i] == name && args.Length > i + 1)
                    return (Util._cachedArgs[name] = args[i + 1]);

            return null;
        }

        /// <summary>
        /// Return the string of an object in a hierarchy, to uniquely identify objects in the scene
        /// </summary>
        /// <param name="obj">Object for which to generate unique name</param>
        /// <returns>Dot-seperated path to the object in the geometry tree</returns>
        public static string ObjectFullName(GameObject obj)
        {
            string res = "";
            bool first = true;
            while(obj != null)
            {
                res = obj.name + (first ? "" : ".") + res;
                first = false;
                obj = (obj.transform.parent == null) ? null : obj.transform.parent.gameObject;
            }
            Regex rgx = new("[^a-zA-Z0-9 -\\.]"); //convert string to a valid filepath
            return rgx.Replace(res, "");
        }

        /// <summary>
        /// Return the matrix projecting from from, through the quad specified
        /// </summary>
        /// <param name="lowerLeft">lower left point of quad</param>
        /// <param name="lowerRight">lower right point of quad</param>
        /// <param name="upperLeft">upper left point of quad</param>
        /// <param name="from">position of the eye</param>
        /// <param name="ncp">near clip plane</param>
        /// <param name="fcp">far clip plane</param>
        /// <returns></returns>
        public static Matrix4x4 GetAsymProjMatrix(Vector3 lowerLeft, Vector3 lowerRight, Vector3 upperLeft, Vector3 from, float ncp, float fcp)
        {
            //compute orthonormal basis for the screen - could pre-compute this...
            Vector3 vr = (lowerRight - lowerLeft).normalized;
            Vector3 vu = (upperLeft - lowerLeft).normalized;
            Vector3 vn = Vector3.Cross(vr, vu).normalized;

            //compute screen corner vectors
            Vector3 va = lowerLeft - from;
            Vector3 vb = lowerRight - from;
            Vector3 vc = upperLeft - from;

            //find the distance from the eye to screen plane
            float d = Vector3.Dot(va, vn); // distance from eye to screen
            float nod = ncp / d;
            float l = Vector3.Dot(vr, va) * nod;
            float r = Vector3.Dot(vr, vb) * nod;
            float b = Vector3.Dot(vu, va) * nod;
            float t = Vector3.Dot(vu, vc) * nod;

            //put together the matrix - bout time amirite?
            Matrix4x4 m = Matrix4x4.zero;

            //from http://forum.unity3d.com/threads/using-projection-matrix-to-create-holographic-effect.291123/
            m[0, 0] = 2.0f * ncp / (r - l);
            m[0, 2] = (r + l) / (r - l);
            m[1, 1] = 2.0f * ncp / (t - b);
            m[1, 2] = (t + b) / (t - b);
            m[2, 2] = -(fcp + ncp) / (fcp - ncp);
            m[2, 3] = (-2.0f * fcp * ncp) / (fcp - ncp);
            m[3, 2] = -1.0f;

            return m;
        }

        /// <summary>
        /// Check if the timeout was specified by the user when running .exe, after timeout the client will close
        /// </summary>
        /// <returns>Integer for timeout</returns>
        public static int GetTimeoutWaitTime()
        {
            string overridden = Util.GetArg("TimeoutWaitTime");

            return overridden != null ? Convert.ToInt32(overridden) : Util.DefaultTimeoutTime;
        }
    }

}