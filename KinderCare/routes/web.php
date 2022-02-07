<?php

use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Route::middleware(['auth:sanctum', 'verified'])->get('/dashboard', function () {
    return view('dashboard');
})->name('dashboard');

Route::get('redirects', 'App\Http\Controllers\HomeController@index');

Route::resource(name:'assign', controller:\App\Http\Controllers\AssignController::class);

Route::resource(name:'enroll', controller:\App\Http\Controllers\EnrollController::class);

Route::resource(name:'deactivate', controller:\App\Http\Controllers\DeactivateController::class);

Route::resource(name:'comment', controller:\App\Http\Controllers\CommentController::class);

Route::resource(name:'reports', controller:\App\Http\Controllers\ReportsController::class);