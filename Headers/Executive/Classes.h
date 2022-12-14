/* Executive Microkernel
 *   Headers/Executive/Classes.h
 *   Defines the Executive's well-known class UUIDs
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef EXECUTIVE_CLASSES_H_
# define EXECUTIVE_CLASSES_H_ 1

#endif /*!EXECUTIVE_CLASSES_H_*/

#if defined(INITGUID) || !defined(EXECUTIVE_CLASSES_H_GUIDS_DEFINED_)
# define EXECUTIVE_CLASSES_H_GUIDS_DEFINED_

/* CLSID_Executive_Root = { 593c6cb3-fe52-494f-98fa-3198023fb6f5 } */
UUID_DEFINE(CLSID_Executive_Root, 0x59, 0x3c, 0x6c, 0xb3, 0xfe, 0x52, 0x49, 0x4f, 0x98, 0xfa, 0x31, 0x98, 0x02, 0x3f, 0xb6, 0xf5);

/* CLSID_Executive_System = { 47a7ba35-db94-4282-a5b6-248fa47e87bf } */
UUID_DEFINE(CLSID_Executive_System, 0x47, 0xa7, 0xba, 0x35, 0xdb, 0x94, 0x42, 0x82, 0xa5, 0xb6, 0x24, 0x8f, 0xa4, 0x7e, 0x87, 0xbf);

/* CLSID_Executive_Network = { 9361d287-d899-4c57-acbc-28f0366f8acc } */
UUID_DEFINE(CLSID_Executive_Network, 0x93, 0x61, 0xd2, 0x87, 0xd8, 0x99, 0x4c, 0x57, 0xac, 0xbc, 0x28, 0xf0, 0x36, 0x6f, 0x8a, 0xcc);

/* CLSID_Executive_Cluster = { 0d14741d-0e15-47dd-9e1b-97381a824093 } */
UUID_DEFINE(CLSID_Executive_Cluster, 0x0d, 0x14, 0x74, 0x1d, 0x0e, 0x15, 0x47, 0xdd, 0x9e, 0x1b, 0x97, 0x38, 0x1a, 0x82, 0x40, 93);

/* CLSID_Executive_Local = { 288a1f1c-89bf-471e-a564-b85137d4b558 } */
UUID_DEFINE(CLSID_Executive_Local, 0x28, 0x8a, 0x1f, 0x1c, 0x89, 0xbf, 0x47, 0x1e, 0xa5, 0x64, 0xb8, 0x51, 0x37, 0xd4, 0xb5, 0x58);

/* CLSID_Executive_Link = { d11b59d3-15ae-4c9d-8df7-5697ad719d77 } */
UUID_DEFINE(CLSID_Executive_Link, 0xd1, 0x1b, 0x59, 0xd3, 0x15, 0xae, 0x4c, 0x9d, 0x8d, 0xf7, 0x56, 0x97, 0xad, 0x71, 0x9d, 0x77);

/* CLSID_Executive_Tasker = { 3a34cbcc-7572-4114-a666-3a5198237902 } */
UUID_DEFINE(CLSID_Executive_Tasker, 0x3a, 0x34, 0xcb, 0xcc, 0x75, 0x72, 0x41, 0x14, 0xa6, 0x66, 0x3a, 0x51, 0x98, 0x23, 0x79, 0x02);

/* CLSID_Executive_Container = { 98602a29-24fb-40e4-bb35-b5c53b6b4afe } */
UUID_DEFINE(CLSID_Executive_Container, 0x98, 0x60, 0x2a, 0x29, 0x24, 0xfb, 0x40, 0xe4, 0xbb, 0x35, 0xb5, 0xc5, 0x3b, 0x6b, 0x4a, 0xfe);

/* CLSID_Executive_Node = { a4cac282-f43a-4005-8266-7d299ce50afd } */
UUID_DEFINE(CLSID_Executive_Node, 0xa4, 0xca, 0xc2, 0x82, 0xf4, 0x3a, 0x40, 0x05, 0x82, 0x66, 0x7d, 0x29, 0x9c, 0xe5, 0x0a, 0xfd);

/* CLSID_Executive_Allocator = { 50ec4a67-4c53-42fb-9d93-7443577b711b } */
UUID_DEFINE(CLSID_Executive_Allocator, 0x50, 0xec, 0x4a, 0x67, 0x4c, 0x53, 0x42, 0xfb, 0x9d, 0x93, 0x74, 0x43, 0x57, 0x7b, 71, 0x1b);

/* CLSID_Executive_Job = */

/* CLSID_Executive_Descriptor = */

/* CLSID_Executive_CooperativeTasker = */

/* CLSID_Executive_CooperativeTasker_Task = */

/* CLSID_Executive_CooperativeTasker_Thread = */

#endif /*INITGUID||!BOOTENVIRONMENT_H_GUIDS_DEFINED_*/
